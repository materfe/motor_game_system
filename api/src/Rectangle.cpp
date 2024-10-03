//
// Created by Mat on 02.10.2024.
//

#include "Rectangle.h"

Rectangle::Rectangle(int posX, int posY, int w, int h, float speedX, float speedY, float grav)
: x(posX), y(posY), width(w), height(h), dx(speedX), dy(speedY), gravity(grav) {}

