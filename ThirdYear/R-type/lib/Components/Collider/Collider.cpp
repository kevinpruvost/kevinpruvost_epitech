#include "Collider.hpp"

#include <algorithm>

using namespace RType::Common::Engine;

Collider::Collider(REngine& engine)
    : RComponent(engine)
{
    callbackOnCollision = [this](const Collider& collider) {
        FixPosition(collider);
    };
}

Collider::~Collider()
{
}

void Collider::Start()
{
}

void Collider::Update()
{
}

void Collider::Tick()
{
}

void Collider::OnCollision(const Collider& collidedCollider)
{
    if (callbackOnCollision)
        callbackOnCollision(collidedCollider);
}

bool Collider::IsCollidingWith(const Collider& othercollider) const
{
    auto myCollisionData = GetCollisionData();
    auto otherCollisionData = othercollider.GetCollisionData();

    if (myCollisionData.colliderType == ColliderType::Circle)
    {
        if (myCollisionData.radius == 0)
            return false;

        if (otherCollisionData.colliderType == ColliderType::Circle)
        {
            if (otherCollisionData.radius == 0)
                return false;

            return IsCircleCollidingWithCircle(
                myCollisionData.point1, myCollisionData.radius,
                otherCollisionData.point1, otherCollisionData.radius);
        }
        else if (otherCollisionData.colliderType == ColliderType::Rectangle)
        {
            return IsRectangleCollidingWithCircle(
                otherCollisionData.point1, otherCollisionData.point2,
                myCollisionData.point1, myCollisionData.radius);
        }
    }
    else if (myCollisionData.colliderType == ColliderType::Rectangle)
    {
        if (myCollisionData.point1.x == myCollisionData.point2.x
         && myCollisionData.point1.y == myCollisionData.point2.y)
            return false;

        if (otherCollisionData.colliderType == ColliderType::Circle)
        {
            if (otherCollisionData.point1.x == otherCollisionData.point2.x
             && otherCollisionData.point1.y == otherCollisionData.point2.y)
                return false;

            return IsRectangleCollidingWithCircle(
                myCollisionData.point1, myCollisionData.point2,
                otherCollisionData.point1, otherCollisionData.radius);
        }
        else if (otherCollisionData.colliderType == ColliderType::Rectangle)
        {
            return IsRectangleCollidingWithRectangle(
                myCollisionData.point1, myCollisionData.point2,
                otherCollisionData.point1, otherCollisionData.point2);
        }
    }
    throw CRITICAL_EXCEPTION("");
}

void Collider::FixPosition(const Collider& obstacle)
{
    Point correctionPoint;

    auto myCollData = GetCollisionData();
    auto oCollData = obstacle.GetCollisionData();

    if (colliderType == ColliderType::Circle)
    {
        if (obstacle.colliderType == ColliderType::Circle)
        {
            float distanceBetweenCenter = myCollData.point1.Distance(oCollData.point1);

            if (distanceBetweenCenter == 0)
            {
                correctionPoint.x = myCollData.radius + oCollData.radius;
                goto endFixCollision;
            }

            float multiplier = (distanceBetweenCenter / (myCollData.radius + oCollData.radius));
            correctionPoint = (myCollData.point1 - oCollData.point1) * ((1 - multiplier) / multiplier);
        }
        else if (obstacle.colliderType == ColliderType::Rectangle)
        {
            correctionPoint = FixPositionBetweenRectangleAndCircle(oCollData, myCollData);
        }
    }
    else if (colliderType == ColliderType::Rectangle)
    {
        if (obstacle.colliderType == ColliderType::Circle)
        {
            correctionPoint = FixPositionBetweenRectangleAndCircle(myCollData, oCollData) * (-1);
        }
        else if (obstacle.colliderType == ColliderType::Rectangle)
        {
            float nearestX[2];
            float nearestY[2];

            if (myCollData.point1.DistanceX(oCollData.point1) >= myCollData.point1.DistanceX(oCollData.point2))
                nearestX[0] = myCollData.point1.DistanceX(oCollData.point1);
            else
                nearestX[0] = myCollData.point1.DistanceX(oCollData.point2);

            if (myCollData.point1.DistanceY(oCollData.point1) >= myCollData.point1.DistanceY(oCollData.point2))
                nearestY[0] = myCollData.point1.DistanceY(oCollData.point1);
            else
                nearestY[0] = myCollData.point1.DistanceY(oCollData.point2);

            if (myCollData.point2.DistanceX(oCollData.point1) >= myCollData.point2.DistanceX(oCollData.point2))
                nearestX[1] = myCollData.point2.DistanceX(oCollData.point1);
            else
                nearestX[1] = myCollData.point2.DistanceX(oCollData.point2);

            if (myCollData.point2.DistanceY(oCollData.point1) >= myCollData.point2.DistanceY(oCollData.point2))
                nearestY[1] = myCollData.point2.DistanceY(oCollData.point1);
            else
                nearestY[1] = myCollData.point2.DistanceY(oCollData.point2);

            if (nearestX[0] >= nearestX[1])
                correctionPoint.x = nearestX[0] - myCollData.point1.x;
            else
                correctionPoint.x = nearestX[1] - myCollData.point2.x;

            if (nearestY[0] >= nearestY[1])
                correctionPoint.y = nearestY[0] - myCollData.point1.y;
            else
                correctionPoint.y = nearestY[1] - myCollData.point2.y;
            
            if (correctionPoint.x >= correctionPoint.y)
                correctionPoint.y = 0;
            else
                correctionPoint.x = 0;
        }
    }
    endFixCollision:

    DEBUG_LOG("Correction point : " << correctionPoint.x << ", " << correctionPoint.y << ".");

    DEBUG_LOG("Position before : " << GetComponent<Transform>().vector.position.x << ", " << GetComponent<Transform>().vector.position.y << ".");

    GetComponent<Transform>().vector.position += correctionPoint;

    DEBUG_LOG("New position : " << GetComponent<Transform>().vector.position.x << ", " << GetComponent<Transform>().vector.position.y << ".");
    myCollData = GetCollisionData();
    oCollData = obstacle.GetCollisionData();
    float distanceBetweenCenter = myCollData.point1.Distance(oCollData.point1);
    DEBUG_LOG("Distance between centers : " << distanceBetweenCenter);
}

float clamp(float val, float min, float max)
{
    return (val < min ? min : (val > max ? max : val));
}

Point Collider::FixPositionBetweenRectangleAndCircle(const CollisionData& rect, const CollisionData& circle)
{
    Point correctionPoint;

    Point nearestPoint;
    nearestPoint.x = clamp(circle.point1.x, rect.point1.x, rect.point2.x);
    nearestPoint.y = clamp(circle.point1.y, rect.point1.y, rect.point2.y);

    DEBUG_LOG("Circle center : " << circle.point1);


    DEBUG_LOG("nearest point : " << nearestPoint);

    if (nearestPoint == circle.point1)
    {
        if (circle.point1.DistanceX(rect.point1) < circle.point1.DistanceX(rect.point2))
            nearestPoint.x = rect.point1.x - circle.radius;
        else
            nearestPoint.x = rect.point2.x + circle.radius;

        if (circle.point1.DistanceY(rect.point1) < circle.point1.DistanceY(rect.point2))
            nearestPoint.y = rect.point1.y - circle.radius;
        else
            nearestPoint.y = rect.point2.y + circle.radius;

        if (nearestPoint.DistanceX(circle.point1) < nearestPoint.DistanceY(circle.point1))
            correctionPoint.x = nearestPoint.x;
        else
            correctionPoint.y = nearestPoint.y;

        return correctionPoint;
    }

    auto director = nearestPoint - circle.point1;

    DEBUG_LOG("director : " << director);

    director.Normalize();

    DEBUG_LOG("normalized director : " << director);

    auto distance = circle.radius - (circle.point1.Distance(nearestPoint));

    director *= -distance;

    correctionPoint += director;

    /*float distanceBetweenLeftTop = circle.point1.Distance(rect.point1);
    float distanceBetweenBottomRight = circle.point1.Distance(rect.point2);

    Point nearestPoint;
    if (distanceBetweenBottomRight < distanceBetweenLeftTop)
    {
        nearestPoint = rect.point2;
        if (circle.point1.x >= circle.radius + nearestPoint.x - 0.1)
            return correctionPoint;
        if (circle.point1.y >= circle.radius + nearestPoint.y - 0.1)
            return correctionPoint;
    }
    else
    {
        nearestPoint = rect.point1;
        if (circle.point1.x <= nearestPoint.x - circle.radius + 0.1)
            return correctionPoint;
        if (circle.point1.y <= nearestPoint.y - circle.radius + 0.1)
            return correctionPoint;
    }

    if (circle.point1.DistanceX(nearestPoint) < circle.point1.DistanceY(nearestPoint))
        correctionPoint.x = circle.point1.DistanceX(nearestPoint);
    else
        correctionPoint.y = circle.point1.DistanceY(nearestPoint);*/

    return director;
}

bool Collider::IsRectangleCollidingWithRectangle(const Point& leftTop1, const Point& bottomRight1, const Point& leftTop2, const Point& bottomRight2) const
{
    if (leftTop1.x >= leftTop2.x && leftTop1.x <= bottomRight2.x)
    {
        if (leftTop1.y >= leftTop2.y && leftTop1.y <= bottomRight2.y)
            return true;
    }
    if (bottomRight1.x >= leftTop2.x && bottomRight1.x <= bottomRight2.x)
    {
        if (bottomRight1.y >= leftTop2.y && bottomRight1.y <= bottomRight2.y)
            return true;
    }
    return false;
}

bool Collider::IsCircleCollidingWithCircle(const Point& circleCenter1, float circleRadius1, const Point& circleCenter2, float circleRadius2) const
{
    if (circleCenter1.Distance(circleCenter2) <= circleRadius2)
        return true;
    if (circleCenter2.Distance(circleCenter1) <= circleRadius1)
        return true;
    return false;
}

bool Collider::IsRectangleCollidingWithCircle(const Point& leftTop, const Point& bottomRight, const Point& circleCenter, float circleRadius) const
{
    Point nearestPoint;
    nearestPoint.x = clamp(circleCenter.x, leftTop.x, bottomRight.x);
    nearestPoint.y = clamp(circleCenter.y, leftTop.y, bottomRight.y);

    if (nearestPoint.Distance(circleCenter) <= circleRadius)
        return true;
    return false;
}

void Collider::UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest)
{
    /*auto convertedComponent = reinterpret_cast<Collider *>(component);

    convertedComponent->ClassName();
    started = convertedComponent->started;
    id = convertedComponent->id;
    entityId = convertedComponent->entityId;
    colliderType = convertedComponent->colliderType;
    colliderLayer = convertedComponent->colliderLayer;*/
}