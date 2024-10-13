//
// Created by Mat on 02.10.2024.
//

#include "Circle.h"

Circle::Circle(const int x, const int y, const int radius, const float dx, const float dy, const float gravity, const float bounce)
: x_(x), y_(y), radius_(radius), dx_(dx), dy_(dy), gravity_(gravity), bounce_(bounce) {}


void Circle::Update(const float deltaTime, const int screenHeight) {
    // Update the circle's position using simple physics
    dy_ += gravity_ * deltaTime;
    x_ += static_cast<int>(dx_ * deltaTime);
    y_ += static_cast<int>(dy_ * deltaTime);

    // Handle collisions with the bottom of the window
    if (y_ + radius_ > screenHeight) {
        y_ = screenHeight - radius_;
        dy_ = -dy_ * bounce_;
    }
}
