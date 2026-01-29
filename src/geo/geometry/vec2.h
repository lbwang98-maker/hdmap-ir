#pragma once

#include <cstdint>

namespace hdmap::geo {

constexpr float kEps = 1e-6f;

struct Vec2 {
  float x{0.f};
  float y{0.f};

  Vec2() = default;
  Vec2(float x_val, float y_val) : x(x_val), y(y_val) {}

  static Vec2 Zero() {
    return Vec2(0.f, 0.f);
  }

  Vec2 operator+(const Vec2& other) const;
  Vec2 operator-(const Vec2& other) const;
  Vec2 operator*(float s) const;
  Vec2 operator/(float s) const;

  Vec2& operator+=(const Vec2& other);
  Vec2& operator-=(const Vec2& other);
  Vec2& operator*=(float s);
  Vec2& operator/=(float s);

  bool operator==(const Vec2& other) const;

  float Dot(const Vec2& other) const;
  float SquaredNorm() const;
  float Norm() const;
  Vec2 Normalized() const;
};

float Cross2D(const Vec2& a, const Vec2& b);
bool NearEqual(const Vec2& a, const Vec2& b, float eps = kEps);
}  // namespace hdmap::geo
