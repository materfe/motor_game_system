//
// Created by Mat on 13.10.2024.
//

#ifndef PLANET_H
#define PLANET_H

#include "common.h"
#include <cmath>

class Planet {
private:
    float x, y;                  // Current position of the circle
    float centerX, centerY;       // Center of the orbit
    float radius;                 // Circle's own radius
    float orbitRadius;            // Radius of the orbit (distance from center point)
    float angularVelocity;        // Speed of the orbit (radians per second)
    float angle;                  // Current angle of rotation (in radians)

public:
    Planet(const float centerX, const float centerY, const float radius, const float orbitRadius, const float angularVelocity)
        : centerX(centerX), centerY(centerY), radius(radius), orbitRadius(orbitRadius),angularVelocity(angularVelocity) {
        angle = 0.0f;
        x = 0.0f;
        y = 0.0f;
        Begin();
    }
    ~Planet() {End();};

    // Initialize circle values (start at the correct position on the orbit)
    void Begin() {
        x = centerX + orbitRadius * std::cos(angle);
        y = centerY + orbitRadius * std::sin(angle);
    }

    // Update the circle's position (move in circular orbit)
    void Update(const float deltaTime) {
        // Update the angle over time using angular velocity
        angle += angularVelocity * deltaTime;

        // Keep angle in the range of [0, 2 * PI]
        if (angle > 2 * PI) {
            angle -= 2 * PI;
        }

        // Calculate the new position based on the updated angle
        x = centerX + orbitRadius * std::cos(angle);
        y = centerY + orbitRadius * std::sin(angle);
    }

    // Handle any cleanup (optional, no specific cleanup here)
    void End() const {
    }

    // Get
    [[nodiscard]] float getX() const { return x; }
    [[nodiscard]] float getY() const { return y; }
    [[nodiscard]] float getRadius() const { return radius; }
};

#endif //PLANET_H
