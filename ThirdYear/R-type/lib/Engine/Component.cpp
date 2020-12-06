#include "Component.hpp"

using namespace RType::Common::Engine;

Component::Component()
{

}

Component::Component(const ComponentId idd)
    : id { idd }
{

}

Component::~Component()
{

}

void Component::Start()
{

}

void Component::Update()
{

}

void Component::Tick()
{
}

void Component::UpdateEngine()
{
}

void Component::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
}

std::string Component::ClassName()
{
    return _className;
}

RType::Common::Udp::Entities::UpdateRequest Component::CreateUpdateRequest()
{

}