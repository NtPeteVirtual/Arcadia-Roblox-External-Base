#pragma once
#include <cmath>
#include <array>

namespace rbx {

    struct vector2
    {
        float X{ 0.0f }, Y{ 0.0f };

        vector2() = default;
        vector2(float x, float y) : X(x), Y(y) {}
        static vector2 New(float x, float y) { return { x, y }; }

        vector2 operator+(const vector2& rhs) const { return { X + rhs.X, Y + rhs.Y }; }
        vector2 operator-(const vector2& rhs) const { return { X - rhs.X, Y - rhs.Y }; }
        vector2 operator*(float scalar) const { return { X * scalar, Y * scalar }; }

        vector2& operator+=(const vector2& rhs) { X += rhs.X; Y += rhs.Y; return *this; }
        vector2& operator-=(const vector2& rhs) { X -= rhs.X; Y -= rhs.Y; return *this; }

        float Magnitude() const { return std::sqrt(X * X + Y * Y); }
        vector2 Normalize() const { float mag = Magnitude(); return { X / mag, Y / mag }; }
    };

    struct vector3
    {
        float X{ 0.0f }, Y{ 0.0f }, Z{ 0.0f };

        vector3() = default;
        vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
        static vector3 New(float x, float y, float z) { return { x, y, z }; }

        vector3 operator+(const vector3& rhs) const { return { X + rhs.X, Y + rhs.Y, Z + rhs.Z }; }
        vector3 operator-(const vector3& rhs) const { return { X - rhs.X, Y - rhs.Y, Z - rhs.Z }; }
        vector3 operator*(float scalar) const { return { X * scalar, Y * scalar, Z * scalar }; }
        vector3 operator*(const vector3& rhs) const { return { X * rhs.X, Y * rhs.Y, Z * rhs.Z }; }
        vector3 operator/(float scalar) const { return { X / scalar, Y / scalar, Z / scalar }; }

        vector3& operator+=(const vector3& rhs) { X += rhs.X; Y += rhs.Y; Z += rhs.Z; return *this; }
        vector3& operator-=(const vector3& rhs) { X -= rhs.X; Y -= rhs.Y; Z -= rhs.Z; return *this; }

        bool operator==(const vector3& rhs) const { return X == rhs.X && Y == rhs.Y && Z == rhs.Z; }

        float Magnitude() const { return std::sqrt(X * X + Y * Y + Z * Z); }
        vector3 Normalize() const { float mag = Magnitude(); return { X / mag, Y / mag, Z / mag }; }
        float Distance(const vector3& v) const { return (*this - v).Magnitude(); }
        vector3 Cross(const vector3& v) const
        {
            return {
                Y * v.Z - Z * v.Y,
                Z * v.X - X * v.Z,
                X * v.Y - Y * v.X
            };
        }
    };


    struct quaternion final { float x, y, z, w; };

    struct matrix3 final { float data[9]; };
    struct matrix4 final { float data[16]; };

    struct cframe
    {
        vector3 RightVector{ 1,0,0 };
        vector3 UpVector{ 0,1,0 };
        vector3 BackVector{ 0,0,1 };
        vector3 Position{ 0,0,0 };

        cframe() = default;
        explicit cframe(const vector3& pos) : Position(pos) {}
        cframe(const vector3& right, const vector3& up, const vector3& back, const vector3& pos)
            : RightVector(right), UpVector(up), BackVector(back), Position(pos) {
        }

        static cframe New(const vector3& pos) { return cframe(pos); }

        cframe LookAt(const vector3& point) const noexcept
        {
            vector3 lookVector = (point - Position).Normalize();
            vector3 rightVector = vector3{ 0,1,0 }.Cross(lookVector);
            vector3 upVector = lookVector.Cross(rightVector);
            return cframe{ rightVector, upVector, lookVector, Position };
        }

        cframe operator*(const cframe& cf) const noexcept
        {
            cframe ret;

            ret.RightVector = {
                RightVector.X * cf.RightVector.X + RightVector.Y * cf.UpVector.X + RightVector.Z * cf.BackVector.X,
                RightVector.X * cf.RightVector.Y + RightVector.Y * cf.UpVector.Y + RightVector.Z * cf.BackVector.Y,
                RightVector.X * cf.RightVector.Z + RightVector.Y * cf.UpVector.Z + RightVector.Z * cf.BackVector.Z
            };
            ret.UpVector = {
                UpVector.X * cf.RightVector.X + UpVector.Y * cf.UpVector.X + UpVector.Z * cf.BackVector.X,
                UpVector.X * cf.RightVector.Y + UpVector.Y * cf.UpVector.Y + UpVector.Z * cf.BackVector.Y,
                UpVector.X * cf.RightVector.Z + UpVector.Y * cf.UpVector.Z + UpVector.Z * cf.BackVector.Z
            };
            ret.BackVector = {
                BackVector.X * cf.RightVector.X + BackVector.Y * cf.UpVector.X + BackVector.Z * cf.BackVector.X,
                BackVector.X * cf.RightVector.Y + BackVector.Y * cf.UpVector.Y + BackVector.Z * cf.BackVector.Y,
                BackVector.X * cf.RightVector.Z + BackVector.Y * cf.UpVector.Z + BackVector.Z * cf.BackVector.Z
            };
            ret.Position = {
                RightVector.X * cf.Position.X + RightVector.Y * cf.Position.Y + RightVector.Z * cf.Position.Z + Position.X,
                UpVector.X * cf.Position.X + UpVector.Y * cf.Position.Y + UpVector.Z * cf.Position.Z + Position.Y,
                BackVector.X * cf.Position.X + BackVector.Y * cf.Position.Y + BackVector.Z * cf.Position.Z + Position.Z
            };
            return ret;
        }

        vector3 operator*(const vector3& vec) const noexcept
        {
            return {
                RightVector.X * vec.X + RightVector.Y * vec.Y + RightVector.Z * vec.Z + Position.X,
                UpVector.X * vec.X + UpVector.Y * vec.Y + UpVector.Z * vec.Z + Position.Y,
                BackVector.X * vec.X + BackVector.Y * vec.Y + BackVector.Z * vec.Z + Position.Z
            };
        }
    };
}