#include "RComponent.hpp"

using namespace RType::Common::Engine;

extern std::unique_ptr<REngine> globalEngine;

RComponent::RComponent(REngine & engine)
    : RAccess(engine)
{
}

RComponent::~RComponent()
{
}

void RComponent::Start()
{
}

void RComponent::Update()
{
}

void RComponent::Tick()
{
}

void RComponent::UpdateEngine()
{
    Update();
}

void RComponent::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
}

RType::Common::Udp::Entities::UpdateRequest RComponent::CreateUpdateRequest()
{
}