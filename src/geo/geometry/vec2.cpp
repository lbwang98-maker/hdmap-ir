#include "geo/geometry/vec2.h"

#include <cmath>

namespace hdmap::geo {

Vec2 Vec2::operator+(const Vec2& other) const {
  return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2& other) const {
  return Vec2(x - other.x, y - other.y);
}

Vec2 Vec2::operator*(float s) const {
  return Vec2(x * s, y * s);
}

Vec2 Vec2::operator/(float s) const {
  return Vec2(x / s, y / s);
}

Vec2& Vec2::operator+=(const Vec2& other) {
  x += other.x;
  y += other.y;
  return *this;
}

Vec2& Vec2::operator-=(const Vec2& other) {
  x -= other.x;
  y -= other.y;
  return *this;
}

Vec2& Vec2::operator*=(float s) {
  x *= s;
  y *= s;
  return *this;
}

Vec2& Vec2::operator/=(float s) {
  x /= s;
  y /= s;
  return *this;
}

bool Vec2::operator==(const Vec2& other) const {
  return NearEqual(*this, other);
}

float Vec2::Dot(const Vec2& other) const {
  return x * other.x + y * other.y;
}

float Vec2::SquaredNorm() const {
  return this->Dot(*this);
}

float Vec2::Norm() const {
  return std::sqrt(SquaredNorm());
}

Vec2 Vec2::Normalized() const {
  float norm = Norm();
  if (norm < kEps) {
    return Vec2::Zero();
  }
  return (*this) / norm;
}

float Cross2D(const Vec2& a, const Vec2& b) {
  return a.x * b.y - a.y * b.x;
}

bool NearEqual(const Vec2& a, const Vec2& b, float eps) {
  return (std::fabs(a.x - b.x) < eps) && (std::fabs(a.y - b.y) < eps);
}

}  // namespace hdmap::geo