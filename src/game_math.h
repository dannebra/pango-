#ifndef _GAME_MATH_
#define _GAME_MATH_

#include <cmath>

namespace GameMath
{
    inline constexpr float pi = 3.14159265;
    inline constexpr float degreeToRadians = pi / 180.0f;
}

struct Vector2
{
    float x;
    float y;

    Vector2(float _x = 0.0f, float _y = 0.0f)
    : x{_x}, y{_y} {}

    float MagnitudeSquared() const
    {
        return (x * x) + (y * y);
    }

    float Magnitude() const
    {
        return sqrt(MagnitudeSquared());
    }

    Vector2 Normalize() const
    {
        float magnitude = Magnitude();
        return Vector2{x / magnitude, y / magnitude};
    }
};

inline Vector2 VectorAdd(const Vector2 &first, const Vector2 &second)
{
    return Vector2{first.x + second.x, first.y + second.y};
}

inline Vector2 VectorSubtract(const Vector2 &first, const Vector2 &second)
{
    return Vector2{first.x - second.x, first.y - second.y};
}

inline Vector2 VectorRotate(const Vector2 &vec, const float angle)
{
    float radAngle = angle * GameMath::degreeToRadians;
    
    return Vector2{
        static_cast<float>((vec.x * cos(radAngle)) - (vec.y * sin(radAngle))),
        static_cast<float>((vec.x * sin(radAngle)) + (vec.y * cos(radAngle)))};
}


#endif