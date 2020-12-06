#include "REngine.hpp"

// Project includes
#include "DebugController.hpp"

using namespace RType::Common::Engine;

REngine::REngine()
    : __systemFactory    { new SystemFactory    }
    , __componentFactory { new ComponentFactory }
    , __entityIdFactory  { new EntityIdFactory  }
{
    DEBUG_LOG("REngine has been created.");
}

REngine::~REngine()
{
    if (__lauchingThread)
    {
        __lauchingThread->join();
        delete __lauchingThread;
    }
    DEBUG_LOG("REngine has been destroyed.");
}

EntityId REngine::CreateEntityId()
{
    auto id = __entityIdFactory->ReserveEntityId();
    auto signature = __entityIdFactory->GetSignature(id);
    __systemFactory->EntitySignatureChanged(id, signature);
    __createdEntities.push_back(id);
    return id;
}

void REngine::DestroyEntityId(EntityId id)
{
    __systemFactory->EntityDestroyed(id);
    __entityIdFactory->FreeEntityId(id);
    __destructedEntities.push_back(id);
}

EntityId REngine::CreateEntityWithId(EntityId id)
{
    return __entityIdFactory->ReserveEntityId(id);
}

float REngine::ComputeDeltaTime()
{
    __endTime = std::chrono::steady_clock::now();

    deltaTime = std::chrono::duration<float, std::chrono::seconds::period>(__endTime - __startTime).count();
    tickTime += deltaTime;

    __startTime = std::chrono::steady_clock::now();
    return deltaTime;
}

bool REngine::Loop()
{
    if (__firstLoop)
    {
        __startTime = std::chrono::steady_clock::now();
        __firstLoop = false;
    }

    auto systems = __systemFactory->GetEverySystems();
    for (auto& system : systems)
    {
        if (system.expired()) continue;

        auto systemPtr = system.lock();

        try
        {
            if (!systemPtr->started)
            {
                systemPtr->Start();
                systemPtr->started = true;
            }
            else
            {
                systemPtr->UpdateEngine();
            }
        }
        catch (const MinorException& e) {
            DEBUG_LOG_ERROR(e.what());
        }
    }

    auto entities = __entityIdFactory->GetEveryEntities();
    for (auto& entity : entities)
    {
        if (entity.expired()) continue;

        auto entityPtr = entity.lock();

        try
        {
            if (!entityPtr->started)
            {
                DEBUG_LOG("Entity start of class : " << entityPtr->ClassName());
                entityPtr->Start();
                entityPtr->started = true;
            }
            else
            {
                DEBUG_LOG("Entity Update");
                entityPtr->UpdateEngine();
            }
        }
        catch (const MinorException& e) {
            DEBUG_LOG_ERROR(e.what());
        }
    }

    auto components = __componentFactory->GetEveryComponents();
    for (auto& component : components)
    {
        if (component.expired()) continue;

        auto componentPtr = component.lock();

        try
        {
            if (!componentPtr->started)
            {
                componentPtr->Start();
                componentPtr->started = true;
            }
            else
            {
                componentPtr->UpdateEngine();
            }
        }
        catch (const MinorException& e) {
            DEBUG_LOG_ERROR(e.what());
        }
    }

    if (__stop)
        return false;

    DEBUG_LOG("Entities size : " << entities.size() << ", components size : " << components.size() << ", systems size : " << systems.size());

    ComputeDeltaTime();

    return true;
}

void REngine::Clear()
{
    __firstLoop = true;
    for (auto& entity : __entityIdFactory->GetEveryEntities())
    {
        if (entity.expired()) continue;
        auto shared = entity.lock();

        DestroyEntityId(shared->getId());
    }
    __stop = false;
}

void REngine::Stop(bool callback)
{
    __stop = true;
    if (callbackOnStop && callback)
        callbackOnStop();
}

void REngine::LoopOnThread()
{
    __lauchingThread = new std::thread([=]() {
        try
        {
            while (!__lastLoopDone)
            {
                if (__paused)
                {
                    __waiting = true;
                    __cPause.notify_all();
                    std::unique_lock<std::mutex> lk(__mutex);
                    __cPause.wait(lk, [=] { return !__paused; });
                }
                __waiting = false;

                try {
                    Loop();
                }
                catch (const MinorException& e) {
                    DEBUG_LOG_ERROR(e.what());
                }
                if (__stop)
                {
                    //__systemFactory.reset();
                    //__componentFactory.reset();
                    //__entityIdFactory->DestroyAll();
                    //__entityIdFactory.reset();
                    __lastLoopDone = true;
                    break;
                }
            }
        }
        catch (const CriticalException& e) {
            LOG_ERROR(e.what());
        }
    });
}

void REngine::Pause(bool set)
{
    if (set)
    {
        __paused = true;
    }
    else
    {
        __paused = false;
        __cPause.notify_all();
    }
}

void REngine::WaitForPause()
{
    if (!__waiting)
    {
        LOG_INFO("Waiting...");
        std::unique_lock<std::mutex> lk(__mutex);
        __cPause.wait(lk, [=] { return __waiting; });
    }
    LOG_INFO("Waiting finished");
}

bool REngine::shouldTick()
{
    __endTime = std::chrono::steady_clock::now();
    tickTime = std::chrono::duration<float, std::chrono::seconds::period>(__endTime - __startTime).count();

    if (tickTime >= 1.f / tickRate)
    {
        LOG_INFO("Should tick !");
        tickTime -= 1.f / tickRate;
        return true;
    }
    return false;
}

std::vector<std::weak_ptr<Component>> REngine::GetCreatedComponents()
{
    std::vector<std::weak_ptr<Component>> createdComponents;
    for (auto ite = __createdComponents.begin(); ite != __createdComponents.end();)
    {
        if (ite->expired()) continue;

        auto shared = ite->lock();

        if (shared->started)
        {
            createdComponents.push_back(*ite);
            __createdComponents.erase(ite);
            ite = __createdComponents.begin();
        }
        else
        {
            ++ite;
        }
    }
    return createdComponents;
}