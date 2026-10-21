#pragma once

namespace ml {
struct Vec2 {
  double x{0};
  double y{0};

  constexpr Vec2& operator*=(double scale) noexcept {
    x *= scale;
    y *= scale;

    return *this;
  }

  constexpr friend Vec2 operator*(const Vec2& v, double scale) noexcept {
    Vec2 result = v;
    result *= scale;
    return result;
  }
  constexpr friend Vec2 operator*(double scale, const Vec2& v) noexcept {
    return v * scale;
  }
};
} // namespace ml