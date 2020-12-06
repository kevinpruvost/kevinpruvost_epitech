#pragma once

#include "Engine/RComponent.hpp"

#include <cmath>

namespace RType
{
namespace Common
{
namespace Engine
{
    /**
     * @brief Contains x and y.
     */
    class Point
    {
    public:
        Point(float xx = 0.f, float yy = 0.f) : x{ xx }, y{ yy } {}
        ~Point() = default;

        void Normalize()
        {
            float div = sqrt(pow(x, 2) + pow(x, 2));
            *this /= div;
        }

        float Distance(const Point & point) const
        {
            return sqrt(pow(point.x - x, 2) + pow(point.y - y, 2));
        }

        float DistanceX(const Point& point) const
        {
            return point.x - x;
        }

        float DistanceY(const Point& point) const
        {
            return point.y - y;
        }

        Point operator+(const Point point)
        {
            Point res = *this;
            res.x += point.x;
            res.y += point.y;
            return res;
        }

        Point& operator+=(const Point& point)
        {
            x += point.x;
            y += point.y;
            return *this;
        }

        Point operator-(const Point point)
        {
            Point res = *this;
            res.x -= point.x;
            res.y -= point.y;
            return res;
        }

        Point& operator-=(const Point& point)
        {
            x -= point.x;
            y -= point.y;
            return *this;
        }

        Point operator/(const float div)
        {
            Point res = *this;
            res.x /= div;
            res.y /= div;
            return res;
        }

        Point operator*(const float mult)
        {
            Point res = *this;
            res.x *= mult;
            res.y *= mult;
            return res;
        }

        Point& operator*=(const float mult)
        {
            x *= mult;
            y *= mult;
            return *this;
        }

        Point& operator/=(const float div)
        {
            x /= div;
            y /= div;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const Point& point)
        {
            os << "[" << point.x << ", " << point.y << "]";
            return os;
        }
        
        bool operator==(const Point& point) const
        {
            return x == point.x && y == point.y;
        }

        bool operator<=(const Point& point) const
        {
            return x <= point.x && y <= point.y;
        }

        bool operator>=(const Point& point) const
        {
            return x >= point.x && y >= point.y;
        }

        bool operator<(const Point& point) const
        {
            return x < point.x && y < point.y;
        }

        bool operator>(const Point& point) const
        {
            return x > point.x&& y > point.y;
        }

        float x;
        float y;
    };
    using Size = Point;

    /**
     * Contains informations on position, rotation and direction.
     */
    class Vector
    {
    public:
        Vector() = default;
        ~Vector() = default;

        Point GetDirection() { return __direction; }
        float GetSpeed() { return __speedPerSeconds; }
        void SetSpeed(float speed) { __speedPerSeconds = speed; }

        /**
         * Moves toward a given position.
         * 
         * \param xx
         * \param yy
         * \param speedPerSeconds
         */
        void MoveTo(float xx, float yy, float speedPerSeconds)
        {
            __direction.x = xx;
            __direction.y = yy;
            __speedPerSeconds = speedPerSeconds;
        }

    public:
        Point position = { 0.f, 0.f };
        Size size = { 0.f, 0.f };
        float rotation = 0.f;

    private:
        Point __direction = { 0.f, 0.f };

        /**
         * @brief Speed in coordinate per seconds.
         * Example : If you want to go from [50, 0] to [150, 0] in 2 seconds, then put 50 speedPerSeconds.
         */
        float __speedPerSeconds = 0.f;
    };

    /**
     * @brief Contains a vector mainly, and the slots linked to their behaviour.
     */
    class Transform : public RComponent
    {
        RCOMPONENT_MANDATORIES(Transform)

    public:
        Transform(REngine & engine);
        ~Transform();

        virtual void UpdateComponent(RType::Common::Udp::Entities::UpdateRequest updateRequest) override;

        void Start() override;
        void Update() override;
        void Tick() override;

        void MoveTo(float x, float y, float speedPerSeconds);

    public:
        Vector vector;
        bool hasMoved = false;
        bool isStatic = false;
        EntityId parentId = Entity::EntityIdNull;
    };
}; // !RType::Common::Engine
}; // !RType::Common
}; // !RType
