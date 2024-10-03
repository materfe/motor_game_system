//
// Created by Mat on 02.10.2024.
//

#ifndef CIRCLE_H
#define CIRCLE_H

class Circle {
private:
    int x, y; // Position of the center
    int radius; // Radius of the circle
    float dx, dy; // Speed in X and Y
    float gravity; // Gravity acceleration
    float bounce; // Bounce coefficient

public:

    Circle(int x, int y, int radius, float dx, float dy, float gravity, float bounce);

    void Update(float deltaTime, int screenHeight);


    //GET
    [[nodiscard]] int getX() const {return x;}
    [[nodiscard]] int getY() const {return y;};
    [[nodiscard]] int getRadius() const {return radius;};
};

#endif //CIRCLE_H
