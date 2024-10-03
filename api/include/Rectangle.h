//
// Created by Mat on 02.10.2024.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private :
    int x, y; // Top-left position
    int width, height; // Dimensions
    float dx, dy; // Velocity in X and Y
    float gravity; // Gravity acceleration

public:

    Rectangle(int posX, int posY, int w, int h, float speedX = 0, float speedY = 0, float grav = 0.0f);


    //GET
    [[nodiscard]] int getX() const {return x;}
    [[nodiscard]] int getY() const {return y;}
    [[nodiscard]] int getWidth() const {return width;}
    [[nodiscard]] int getHeight() const {return height;}
};

#endif // RECTANGLE_H
