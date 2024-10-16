//
// Created by Mat on 15.10.2024.
//

#include "planet.h"
#include "common.h"
#include <cmath>

void Planet::Begin()
{
    x_ = center_x_ + orbit_radius_ * std::cos(angle_);
    y_ = center_y_ + orbit_radius_ * std::sin(angle_);
}

void Planet::Update(const float deltaTime)
{
    //early exit
    if(common::AproximateZeroForFloats(radius_))
    {
        return;
    }

    // Update the angle over time using angular velocity
    angle_ += angular_velocity_ * deltaTime;

    // Keep angle in radians
    if (angle_ > 2 * PI) {
        common::ToRadians(angle_);
    }

    // Calculate the new position based on the updated angle
    x_ = center_x_ + orbit_radius_ * std::cos(angle_);
    y_ = center_y_ + orbit_radius_ * std::sin(angle_);
}
