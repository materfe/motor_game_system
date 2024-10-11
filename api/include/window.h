//
// Created by Mat on 02.10.2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class window {
public:
    SDL_Window* window_;

    window(const char* title, int width, int height);

    ~window();
};

#endif //WINDOW_H
