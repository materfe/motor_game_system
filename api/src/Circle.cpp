//
// Created by Mat on 02.10.2024.
//

#include "Circle.h"

Circle::Circle(const int x, const int y, const int radius, const float dx, const float dy, const float gravity, const float bounce)
: x(x), y(y), radius(radius), dx(dx), dy(dy), gravity(gravity), bounce(bounce) {}


void Circle::Update(const float deltaTime, const int screenHeight) {
    // Update the circle's position using simple physics
    dy += gravity * deltaTime;
    x += static_cast<int>(dx * deltaTime);
    y += static_cast<int>(dy * deltaTime);

    // Handle collisions with the bottom of the window
    if (y + radius > screenHeight) {
        y = screenHeight - radius;
        dy = -dy * bounce;
    }
}
