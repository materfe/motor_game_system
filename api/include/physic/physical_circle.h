//
// Created by Mat on 30.10.2024.
//

#ifndef GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_
#define GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_

#include "physical_shape.h"
#include "aabb.h"

class PhysicalCircle final : public PhysicalShape {
 private:
  float radius_;
  AABB bounds_{};

 public:
  PhysicalCircle(core::Vec2<float> position, float mass, float radius) : PhysicalShape(position, mass),
                                                                         radius_(radius) {
    bounds_.UpdatePos(position_.x_ - radius, position_.y_ - radius_,
                      position_.x_ + radius_, position_.y_ + radius_);
  }

  PhysicalCircle(core::Vec2<float> position, core::Vec2<float> velocity, float mass, float radius) :
      PhysicalShape(position, velocity, mass), radius_(radius) {
    bounds_.UpdatePos(position_.x_ - radius, position_.y_ - radius_,
                      position_.x_ + radius_, position_.y_ + radius_);
  }

  PhysicalCircle(core::Vec2<float> position, float radius) : PhysicalShape(position, 0.0f), radius_(radius) {
    bounds_.UpdatePos(position_.x_ - radius_, position_.y_ - radius_,
                      position_.x_ + radius_, position_.y_ + radius_);
  }

  PhysicalCircle() : PhysicalShape(core::Vec2<float>::Zero(), 0.0f), radius_(0.0f) {
    bounds_.UpdatePos(position_.x_ - radius_, position_.y_ - radius_,
                      position_.x_ + radius_, position_.y_ + radius_);
  }

  void Update(const float delta_time, const float max_x_bound, const float max_y_bound);

  //GET
  [[nodiscard]] float GetRadius() const { return radius_; }
  [[nodiscard]] AABB &bounds() { return bounds_; }
};

struct PhysicalCirclePair {
  // Helper structure to store a unique pair of circles

  PhysicalCircle *circle1; // Pointer to the first circle
  PhysicalCircle *circle2; // Pointer to the second circle

  // Ensure unique ordering of pairs by sorting the pointers
  bool operator<(const PhysicalCirclePair &other) const {
    return std::tie(circle1, circle2) < std::tie(other.circle1, other.circle2);
  }
  bool operator==(const PhysicalCirclePair &other) const {
    // Compare both elements in the pair (unordered comparison)
    return (circle1 == other.circle1 && circle2 == other.circle2) ||
        (circle1 == other.circle2 && circle2 == other.circle1);
  }
};
namespace std {
template<>
struct hash<PhysicalCirclePair> {
  std::size_t operator()(const PhysicalCirclePair &pair) const {
    // Combine hashes of the two pointers, treating (A, B) the same as (B, A)
    auto h1 = std::hash<const PhysicalCircle *>()(pair.circle1);
    auto h2 = std::hash<const PhysicalCircle *>()(pair.circle2);
    return h1 ^ h2; // XOR the two hashes for symmetry
  }
};
}

#endif //GAME_MOTOR_ENGINE_API_INCLUDE_PHYSIC_PHYSICAL_CIRCLE_H_
