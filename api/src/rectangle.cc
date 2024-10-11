//
// Created by Mat on 02.10.2024.
//

#include "rectangle.h"

rectangle::rectangle(int posX, int posY, int w, int h, float speedX, float speedY, float grav)
: x_(posX), y_(posY), width_(w), height_(h), dx_(speedX), dy_(speedY), gravity_(grav) {}

