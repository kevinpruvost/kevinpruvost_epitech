#include "UITransform.hpp"

using namespace RType::Common::Engine;

UITransform::UITransform(REngine& engine)
    : RComponent(engine)
{
}

UITransform::~UITransform()
{
}

void UITransform::Start()
{
}

void UITransform::Update()
{
}

void UITransform::Tick()
{
}

void UITransform::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    position.x = updateRequest.uiTransform.positionX;
    position.y = updateRequest.uiTransform.positionY;
    size.x = updateRequest.uiTransform.sizeX;
    size.y = updateRequest.uiTransform.sizeY;
    centered = updateRequest.uiTransform.centered;
}