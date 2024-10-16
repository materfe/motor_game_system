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

void Planet::Begin() {
  x_ = center_x_ + orbit_radius_ * std::cos(angle_);
  y_ = center_y_ + orbit_radius_ * std::sin(angle_);
}


void Planet::Update(const float delta_time) {

#ifdef TRACY_ENABLE
    ZoneScoped;
#endif

	//early exit
  if (common::AproximateZeroForFloats(orbit_radius_)) {
    return;
  }

  // Update the angle over time using angular velocity
  angle_ += common::ToMeters(angular_velocity_) * delta_time;

  // Keep angle in radians
  if (angle_ > 2 * PI) {
    common::ToRadians(angle_);
  }

  // Calculate the new position based on the updated angle
  x_ = center_x_ + orbit_radius_ * std::cos(angle_);
  y_ = center_y_ + orbit_radius_ * std::sin(angle_);
}

void Planet::SetVariablesToZeroAndColor() {
  angle_ = 0.0f;
  x_ = 0.0f;
  y_ = 0.0f;
  color_[0] = common::GenerateANumber(255);
  color_[1] = common::GenerateANumber(255);
  color_[2] = common::GenerateANumber(255);
}

