//
// Created by Mat on 13.10.2024.
//

#ifndef PLANET_H
#define PLANET_H

class Planet {
private:
    float x_, y_;                  // Current position of the circle
    float center_x_, center_y_;       // Center of the orbit
    float radius_;                 // Circle's own radius
    float orbit_radius_;            // Radius of the orbit (distance from center point)
    float angular_velocity_;        // Speed of the orbit (radians per second)
    float angle_;                  // Current angle of rotation (in radians)

public:
    Planet(const float centerX, const float centerY, const float radius, const float orbitRadius, const float angularVelocity)
        : center_x_(centerX), center_y_(centerY), radius_(radius), orbit_radius_(orbitRadius),angular_velocity_(angularVelocity) {
        angle_ = 0.0f;
        x_ = 0.0f;
        y_ = 0.0f;
        Begin();
    }
    ~Planet() {End();};

    // Initialize circle values (start at the correct position on the orbit)
    void Begin();

    // Update the circle's position (move in circular orbit)
    void Update(float deltaTime);

    // Handle any cleanup (optional, no specific cleanup here)
    void End() const {
    }

    // Get
    [[nodiscard]] float getX() const { return x_; }
    [[nodiscard]] float getY() const { return y_; }
    [[nodiscard]] float getRadius() const { return radius_; }
};

#endif //PLANET_H
