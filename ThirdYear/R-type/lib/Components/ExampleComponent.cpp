#include "ExampleComponent.hpp"

using namespace RType::Common::Engine;

ExampleComponent::ExampleComponent(REngine& engine)
    : RComponent(engine)
{
}

ExampleComponent::~ExampleComponent()
{
}

void ExampleComponent::Start()
{
}

void ExampleComponent::Update()
{
}

void ExampleComponent::Tick()
{
}

void ExampleComponent::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest ud)
{
}
