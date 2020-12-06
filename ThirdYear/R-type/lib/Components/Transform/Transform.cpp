#include "Transform.hpp"

using namespace RType::Common::Engine;

Transform::Transform(REngine& engine)
    : RComponent(engine)
{
}

Transform::~Transform()
{
}

void Transform::Start()
{
}

void Transform::Update()
{
}

void Transform::Tick()
{
}

void Transform::MoveTo(float x, float y, float speedPerSeconds)
{
    vector.MoveTo(x, y, speedPerSeconds);
}

void Transform::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    vector.position.x = updateRequest.transform.positionX;
    vector.position.y = updateRequest.transform.positionY;
    vector.size.x = updateRequest.transform.sizeX;
    vector.size.y = updateRequest.transform.sizeY;
    vector.MoveTo(updateRequest.transform.directionX,
                  updateRequest.transform.directionY,
                  updateRequest.transform.speed);
    hasMoved = updateRequest.transform.hasMoved;
    isStatic = updateRequest.transform.isStatic;
    parentId = updateRequest.transform.parentId;
}