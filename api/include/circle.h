//
// Created by Mat on 02.10.2024.
//

#ifndef CIRCLE_H
#define CIRCLE_H

class circle {
private:
    int x_, y_; // Position of the center
    int radius_; // Radius of the circle
    float dx_, dy_; // Speed in X and Y
    float gravity_; // Gravity acceleration
    float bounce_; // Bounce coefficient

public:

    circle(int x, int y, int radius, float dx, float dy, float gravity, float bounce);

    void Update(float deltaTime, int screenHeight);


    //GET
    [[nodiscard]] int getX() const {return x_;}
    [[nodiscard]] int getY() const {return y_;};
    [[nodiscard]] int getRadius() const {return radius_;};
};

#endif //CIRCLE_H
