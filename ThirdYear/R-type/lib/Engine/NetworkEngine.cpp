#include "NetworkEngine.hpp"

using namespace RType::Common::Engine;

RType::Common::Rfc::ComponentTypeId NetworkEngine::GetComponentTypeIdFromComponent(const std::weak_ptr<Component>& component)
{
    if (component.expired()) throw CRITICAL_EXCEPTION("Trying to get componenttypeid of inexsitant component.");

    auto shared = component.lock();
    return GetComponentTypeIdFromComponent(*shared);
}

RType::Common::Rfc::ComponentTypeId NetworkEngine::GetComponentTypeIdFromComponent(Component& component)
{
    auto name = component.ClassName();

    return RType::Common::Rfc::ComponentTypeId::Audio;
}
