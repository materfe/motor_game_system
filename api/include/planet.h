//
// Created by Mat on 13.10.2024.
//

#ifndef PLANET_H
#define PLANET_H

#include "common.h"
#include "vec2.h"
#include <array>

static constexpr float G = 6.67430e-11f;

class Planet {
 private:
  core::Vec2<float> position_;                // Current position of the circle
  core::Vec2<float> angular_velocity_;        // Speed of the orbit (radians per second [currently per frame])
  core::Vec2<float> acceleration_;            //acceleration of the planet
  float radius_;                    // Circle's radius
  float mass_;                      //mass in kilogram
  std::array<int, 4> color_{};

 public:
  Planet(const float radius, const core::Vec2<float> position, const core::Vec2<float> angularVelocity,
         const float mass) : radius_(radius), position_(position), angular_velocity_(angularVelocity),
                             mass_(mass) {

    acceleration_ = core::Vec2<float>(0.0f, 0.0f);

    SetRandomColor();
  }

  Planet() {
    position_ = core::Vec2<float>(0.0f, 0.0f);
    acceleration_ = core::Vec2<float>(0.0f, 0.0f);
    radius_ = 0.0f;
    angular_velocity_.x_ = 0.0f;
    angular_velocity_.y_ = 0.0f;
    color_ = std::array<int, 4>{0, 0, 0, 0};
    mass_ = 0.0f;
  }

  void ApplyGravitationalForce(float sun_mass, const core::Vec2<float> &sun_position);

  // Update the position and velocity of the planet
  void SumTheForcesAndMoveThePlanet(float delta_time);

  ~Planet() { End(); };

  //set and colors
  void SetRandomColor();

  // Update the circle's position (move in circular orbit)
  void Update(float delta_time, float sun_mass, const core::Vec2<float> &sun_position);

  // Handle any cleanup (optional, no specific cleanup here)
  void End() const {}

  // Get
  [[nodiscard]] float getX() const { return position_.x_; }
  [[nodiscard]] float getY() const { return position_.y_; }
  [[nodiscard]] float getRadius() const { return radius_; }
  [[nodiscard]] std::array<int, 4> getColor() const { return color_; }
};

#endif //PLANET_H
