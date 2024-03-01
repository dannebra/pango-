#ifndef _GAME_MATH_
#define _GAME_MATH_

#include <cmath>

namespace GameMath
{
    inline constexpr float pi = 3.14159265f;
    inline constexpr float degreeToRadians = pi / 180.0f;
}

namespace Vector 
{
    struct Vector2
    {
        float x;
        float y;

        constexpr Vector2(float _x = 0.0f, float _y = 0.0f)
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

        Vector2 &Add(Vector::Vector2 offset)
        {
            x += offset.x;
            y += offset.y;

            return *this;
        }

        Vector2 &Subtract(Vector::Vector2 offset)
        {
            x -= offset.x;
            y -= offset.y;

            return *this;
        }
    };

    inline Vector2 Add(const Vector2 &first, const Vector2 &second)
    {
        return Vector2{first.x + second.x, first.y + second.y};
    }

    inline Vector2 Subtract(const Vector2 &first, const Vector2 &second)
    {
        return Vector2{first.x - second.x, first.y - second.y};
    }

    inline Vector2 Multiply(const Vector2 &vec, const float factor)
    {
        return Vector2(vec.x * factor, vec.y * factor);
    }

    inline Vector2 Rotate(const Vector2 &vec, const float angle)
    {
        float radAngle = angle * GameMath::degreeToRadians;
        
        return Vector2{
            static_cast<float>((vec.x * cos(radAngle)) - (vec.y * sin(radAngle))),
            static_cast<float>((vec.x * sin(radAngle)) + (vec.y * cos(radAngle)))};
    }

    inline constexpr Vector2 VECTOR2_ZERO{0.0f, 0.0f};
    inline constexpr Vector2 VECTOR2_ONE{1.0f, 1.0f};
    inline constexpr Vector2 VECTOR2_UP{0.0f, 1.0f};
    inline constexpr Vector2 VECTOR2_RIGHT{1.0f, 0.0f};
}

#endif