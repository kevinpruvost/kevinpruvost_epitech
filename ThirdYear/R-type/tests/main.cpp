#define BOOST_TEST_MODULE rtype_test_module

// Google test includes
#include "gtest/gtest.h"
#include <boost/filesystem.hpp>

// Project includes
#include "DebugController.hpp"
#include "FileSystemWatcher/RTypeFileSystemWatcher.hpp"

    // DLLoader
    #include "DLLoader/RTypeDLLoader.hpp"

    // Engine
    #include "Engine/REngine.hpp"
    #include "Engine/REntity.hpp"

// Test includes
    
    // Engine
    #include "Engine/TestComponent.hpp"
    #include "Engine/TestSystem.hpp"
    #include "Engine/TestEntity.hpp"

using namespace RType;
using namespace Common;

// C++ includes
#include <vector>
#include <memory>
#include <random>

// Macro defines for test
#define RENGINE_TEST
//#define DLLOADER_TEST

/**
*
*  DLLOADER UNIT TESTS
*
*/

#ifdef DLLOADER_TEST

extern "C" {
#ifdef __unix__
    char* linux_get_path();
    void linux_free_path(char* path);
#elif _WIN32
    char* windows_get_path();
    void windows_free_path(char* path);
#endif
}

/* TODO getCurrentPath en cpp proprement sans fonction C */
/* TODO push toutes les .so et .dll */

TEST(DLLoader, REntity)
{
    RType::Common::DLLoader::RTypeDLLoader<RType::Common::Engine::Entity> r("/home/bardo/r-type/tests/merde.so");
    RType::Common::Engine::REngine q;

    if (r == nullptr) {
        EXPECT_TRUE(!(r == nullptr));
        return;
    }
    
    //auto t = (r.getInstance("getClass"));
    //if (t == nullptr)
    //    std::cout << "ça fait chier" << std::endl;
    //t->Start();
}

TEST(DLLoader, loadClass)
{
    std::string path;

    #ifdef __unix__
        path = linux_get_path();
        path.append("/build/lib/libtestDLLoader.so");
    #elif _WIN32
        path = windows_get_path();
        path.append("/build/lib/libtestDLLoader.dll");
    #endif
    RType::Common::DLLoader::RTypeDLLoader<RType::Common::Engine::Entity> r(path);

    EXPECT_TRUE(!(r == nullptr));
}

TEST(DLLoader, loadNonExistantFile)
{
    RType::Common::DLLoader::RTypeDLLoader<RType::Common::Engine::Entity> r("notevenadll");

    EXPECT_TRUE(r == nullptr);
}

TEST(DLLoader, loadEmptyFile)
{
    RType::Common::DLLoader::RTypeDLLoader<RType::Common::Engine::Entity> r("empty.so");

    EXPECT_TRUE(r == nullptr);
}

TEST(DLLoader, loadParentClassInstance)
{
    std::string path;

    #ifdef __unix__
        path = linux_get_path();
        path.append("/build/lib/libtestDLLoader.so");
    #elif _WIN32
        path = windows_get_path();
        path.append("build\\bin\\testDLLoader.dll");
    #endif

    RType::Common::DLLoader::RTypeDLLoader<RType::Common::Engine::Entity> r(path);
    RType::Common::Engine::REngine q;

    if (r == nullptr) {
        EXPECT_TRUE(!(r == nullptr));
        return;
    }
    
    auto t = (r.getInstance("getClass", q));
    EXPECT_TRUE((t != nullptr));
    if (t)
        t->Tick();
}

TEST(FileWatcher, filewatcher)
{

    RType::Common::FileSystemWatcher::RTypeFileSystemWatcher f("./");
    std::list<std::string> list = f.getFolderFile();

    for (auto & l : list)
        std::cout << l << std::endl;
}

#endif // !DLLOADER_TEST

/**
*
*  RENGINE UNIT TESTS
*
*/

#ifdef RENGINE_TEST

TEST(REngine, REntityTest)
{
    Engine::REngine engine;
    Engine::REntity entity(engine);
}

TEST(REngine, EntityIdsLightConstructionAndDestruction)
{
    Engine::REngine engine;
    std::unique_ptr<Engine::REntity> entities[50];
    for (Engine::EntityId i = 0; i < 50; ++i)
    {
        entities[i].reset(new Engine::REntity(engine));
        EXPECT_EQ(entities[i]->getId(), i);
    }

    // Creates scope for the next 50 entities so that they destroy
    // themselves after the test.
    {
        std::unique_ptr<Engine::REntity> entities2[50];
        for (Engine::EntityId i = 0; i < 50; ++i)
        {
            entities2[i].reset(new Engine::REntity(engine));
            EXPECT_EQ(entities2[i]->getId(), i + 50);
        }
    }

    // Tests if the previously 50 entities removed ids are taken.
    Engine::Entity entities2[50];
    for (Engine::EntityId i = 0; i < 50; ++i)
    {
        entities2[i].setId(engine.CreateEntityId());
        EXPECT_EQ(entities2[i].getId(), i + 50);
    }
}

TEST(REngine, EntityIdsRandomDestruction)
{
    Engine::REngine engine;
    std::vector<std::unique_ptr<Engine::Entity>> entities;
    size_t entitiesNumber = rand() % 150;

    for (size_t i = 0; i < entitiesNumber; ++i)
        entities.emplace_back(new Engine::Entity);

    std::vector<Engine::EntityId> randomIdsDestroyed;

    for (size_t i = 0; i < entitiesNumber && i < entities.size(); i += rand() % 4)
    {
        randomIdsDestroyed.push_back(entities[i]->getId());
        entities.erase(entities.begin() + i);
    }

    std::vector<std::unique_ptr<Engine::Entity>> newEntities;

    for (size_t i = 0; i < randomIdsDestroyed.size(); ++i)
        newEntities.emplace_back(new Engine::Entity);

    // Tests if the destroyed entities ids are taken well.
    for (size_t i = 0; i < randomIdsDestroyed.size(); ++i)
        EXPECT_EQ(newEntities[i]->getId(), randomIdsDestroyed[i]);

    // Tests if the ids are all below the entities number.
    for (auto & ptr : entities)
        EXPECT_LT(ptr->getId(), entitiesNumber);

    for (auto & ptr : newEntities)
        EXPECT_LT(ptr->getId(), entitiesNumber);
}

TEST(REngine, ComponentCreationAndGetTest)
{
    Engine::REngine engine;

    Engine::Entity entity(engine.CreateEntityId());
    engine.RegisterComponent<Engine::RComponent>(Rfc::ComponentTypeId::Audio);
    //engine.AddComponent(entity.getId(), Engine::Test::TestComponent(engine));
    //EXPECT_NO_THROW(engine.GetComponent<Engine::Test::TestComponent>(entity.getId()).sayCoom());
}

TEST(REngine, ComponentModificationTest)
{
    Engine::REngine engine;

    Engine::Entity entity(engine.CreateEntityId());
    //engine.RegisterComponent<Engine::Test::TestComponent>();
    //engine.AddComponent(entity.getId(), Engine::Test::TestComponent(engine));
    
    //auto & testComp = engine.GetComponent<Engine::Test::TestComponent>(entity.getId());

    int testInt = rand() % 99;
    //testComp.testVar = testInt;

    //EXPECT_EQ(engine.GetComponent<Engine::Test::TestComponent>(entity.getId()).testVar, testInt);
}

TEST(REngine, ComponentModificationTestWithREntity)
{
    Engine::REngine engine;

    engine.RegisterComponent<Engine::RComponent>(Rfc::ComponentTypeId::Audio);
    Engine::Test::TestEntity entity(engine);
    entity.Start();
    Engine::REntity entity2 = entity;
    entity2.Start();
    //engine.RegisterComponent<Engine::Test::TestComponent>();
    //engine.AddComponent(entity.getId(), Engine::Test::TestComponent(engine));

    //auto& testComp = engine.GetComponent<Engine::Test::TestComponent>(entity.getId());

    int testInt = rand() % 99;
    //testComp.testVar = testInt;

    //EXPECT_EQ(entity.GetComponent<Engine::Test::TestComponent>(entity.getId()).testVar, testInt);
}

TEST(REngine, SystemCreationAndGetTest)
{
    Engine::REngine engine;

    //engine.RegisterComponent<Engine::Test::TestComponent>();
    //auto system = engine.RegisterSystem<Engine::Test::TestSystem>(engine);

    //system->Start();
}

TEST(REngine, REntityWithRComponentsTest)
{
    Engine::REngine engine;

    //engine.RegisterComponent<Engine::Test::TestComponent>();

    //Engine::Test::TestEntity testEntity(engine);
    //testEntity.AddComponent<Engine::Test::TestComponent>();

}

TEST(REngine, RAccess)
{
    Engine::REngine engine;

    engine.RegisterComponent<Engine::Test::TestComponent>(Rfc::ComponentTypeId::Audio);

    Engine::REntity entity(engine);
    Engine::REntity entity2(engine);

    entity2.AddComponent<Engine::Test::TestComponent>();
    entity2.AddComponent<Engine::Test::TestComponent>();
    entity2.AddComponent<Engine::Test::TestComponent>();

    auto list = entity.FindComponents<Engine::Test::TestComponent>();
    EXPECT_EQ(list.size(), 3);
}

#include "Systems/ColliderSystem.hpp"
#include "Engine/ColliderTest.hpp"

#include "Components/UITransform/UITransform.hpp"

TEST(REngine, ColliderSystemTest)
{
    Engine::REngine engine;

    engine.RegisterComponent<Engine::Transform>(Rfc::ComponentTypeId::Transform);
    engine.RegisterComponent<Engine::UITransform>(Rfc::ComponentTypeId::UITransform);
    engine.RegisterComponent<Engine::RectangleCollider>(Rfc::ComponentTypeId::RectangleCollider);
    engine.RegisterComponent<Engine::CircleCollider>(Rfc::ComponentTypeId::CircleCollider);
    engine.CreateEntity<Engine::Test::ColliderTest>(engine);
    //engine.RegisterEntity(entity);
    auto colliderSystem = engine.RegisterSystem<Engine::ColliderSystem>(engine);
    //engine.Instantiate<Engine::Test::ColliderTest>();
    //Engine::Test::ColliderTest entity(engine);
    //Engine::Test::ColliderTest entity2(engine);
    //entity.AddComponent<Engine::RectangleCollider>();
    //entity2.AddComponent<Engine::CircleCollider>();
    //engine.RegisterEntity(entity, entity.ClassName());
    //auto otherEntity = engine.CreateEntityFromClassName(entity.ClassName());
    //colliderSystem->Start();
    //entity.Start();
    //entity2.Start();
    //entity.GetComponent<Engine::Transform>().vector.position += rand() % 100 / 50.f;
    //entity2.GetComponent<Engine::Transform>().vector.position += rand() % 100 / 50.f;
    engine.Loop();
}

#include "Systems/RenderingSystem.hpp"
#include "Game/TitleScreen.hpp"
#include "Game/FpsDisplayer.hpp"
#include "Components/AllComponents.hpp"

TEST(REngine, SfmlTest)
{
    Engine::REngine engine;

    engine.RegisterComponent<Engine::Transform>(Rfc::ComponentTypeId::Transform);
    engine.RegisterComponent<Engine::UITransform>(Rfc::ComponentTypeId::UITransform);
    engine.RegisterComponent<Engine::RectangleCollider>(Rfc::ComponentTypeId::RectangleCollider);
    engine.RegisterComponent<Engine::CircleCollider>(Rfc::ComponentTypeId::CircleCollider);
    engine.RegisterComponent<Engine::SpriteAnimation>(Rfc::ComponentTypeId::SpriteAnimation);
    engine.RegisterComponent<Engine::Sprite>(Rfc::ComponentTypeId::Sprite);
    engine.RegisterComponent<Engine::Text>(Rfc::ComponentTypeId::Text);
    engine.CreateEntity<Engine::Test::ColliderTest>(engine);
    engine.CreateEntity<Engine::TitleScreen>(engine);
    auto fpsd = engine.CreateEntity<Engine::FpsDisplayer>(engine);
    //engine.RegisterEntity(entity);
    auto colliderSystem = engine.RegisterSystem<Engine::ColliderSystem>(engine);
    auto sfmlSystem = engine.RegisterSystem<Engine::RenderingSystem>(engine);

    engine.AddComponent(fpsd->getId(), Engine::Transform(engine));
    engine.AddComponent(fpsd->getId(), Engine::CircleCollider(engine));
    auto & entity = engine.GetComponent<Engine::CircleCollider>(fpsd->getId());

    DEBUG_LOG(entity.entityId);

    void* entityBase = reinterpret_cast<void*>(&entity);
    void* newEntity = operator new(sizeof(Engine::CircleCollider));
    
    memcpy(newEntity, entityBase, sizeof(Engine::CircleCollider));
    auto newEntityConv = reinterpret_cast<Engine::CircleCollider*>(newEntity);

    DEBUG_LOG(newEntityConv->entityId);

    delete newEntity;
    DEBUG_LOG((int)entity.GetComponentTypeId());

    std::vector<size_t> sizes;
    sizes.push_back(sizeof(Engine::CircleCollider));
    sizes.push_back(sizeof(Engine::RectangleCollider));
    sizes.push_back(sizeof(Engine::Collider));
    sizes.push_back(sizeof(Engine::Button));
    sizes.push_back(sizeof(Engine::Audio));
    sizes.push_back(sizeof(Engine::CharacterCharacteristics));
    sizes.push_back(sizeof(Engine::Weapon));
    sizes.push_back(sizeof(Engine::KeyInput));
    sizes.push_back(sizeof(Engine::Sprite));
    sizes.push_back(sizeof(Engine::SpriteAnimation));
    sizes.push_back(sizeof(Engine::Text));
    sizes.push_back(sizeof(Engine::Transform));
    sizes.push_back(sizeof(Engine::TextInput));
    sizes.push_back(sizeof(Engine::UITransform));
    for (auto& key : sizes)
    {
        DEBUG_LOG("Size : " << key);
    }
    //engine.LoopOnThread();
}

#endif // !RENGINE_TEST

int main(int argc, char **argv)
{
    DebugController::setDebugMode(true);
    srand((unsigned int)(time(NULL)));
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}