//
// Created by Mat on 15.10.2024.
//

#include "planet.h"
#include "common.h"
#include <cmath>
#ifdef TRACY_ENABLE
#include <tracy/Tracy.hpp>
#include <tracy/TracyC.h>
#endif

//functions used in Update() -> calculate gravity and velocity to move planet
void Planet::ApplyGravitationalForce(const float sun_mass, const core::Vec2<float> &sun_position) {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  const float direction_for_x = sun_position.x_ - position_.x_;
  const float direction_for_y = (sun_position.y_ - position_.y_);

  const float actual_distance = std::sqrt(direction_for_x * direction_for_x + direction_for_y * direction_for_y);
  const double gravitational_force = (G * mass_ * sun_mass) / (std::pow(actual_distance, 2));

  // Normalizing the direction of the gravitational_force
  double force_x = gravitational_force * (direction_for_x / actual_distance);
  double force_y = gravitational_force * (direction_for_y / actual_distance);

  // Update acceleration using F = m * a, so a = F / m
  acceleration_.x_ = static_cast<float>(force_x) / mass_;
  acceleration_.y_ = static_cast<float>(force_y) / mass_;
}
void Planet::SumTheForcesAndMoveThePlanet(const float delta_time) {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  // Update velocity: v = v + a * dt
  angular_velocity_.x_ += acceleration_.x_ * delta_time;
  angular_velocity_.y_ += acceleration_.y_ * delta_time;

  // Update position: p = p + v * dt
  position_.x_ += angular_velocity_.x_ * delta_time;
  position_.y_ += angular_velocity_.y_ * delta_time;
}

void Planet::Update(const float delta_time, const float sun_mass, const core::Vec2<float>& sun_position) {

#ifdef TRACY_ENABLE
    ZoneScoped;
#endif

  ApplyGravitationalForce(sun_mass, sun_position);
  SumTheForcesAndMoveThePlanet(delta_time);
}

void Planet::SetRandomColor() {
  for(auto& c : color_)
  {
    c = common::GenerateRandomNumber(0, 255);
  }
}

