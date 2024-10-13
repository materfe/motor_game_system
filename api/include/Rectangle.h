//
// Created by Mat on 02.10.2024.
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle {
private :
    int x_, y_; // Top-left position
    int width_, height_; // Dimensions
    float dx_, dy_; // Velocity in X and Y
    float gravity_; // Gravity acceleration

public:

    Rectangle(int posX, int posY, int w, int h, float speedX = 0, float speedY = 0, float grav = 0.0f);


    //GET
    [[nodiscard]] int getX() const {return x_;}
    [[nodiscard]] int getY() const {return y_;}
    [[nodiscard]] int getWidth() const {return width_;}
    [[nodiscard]] int getHeight() const {return height_;}
};

#endif // RECTANGLE_H
