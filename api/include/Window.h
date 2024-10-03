//
// Created by Mat on 02.10.2024.
//

#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window {
public:
    SDL_Window* window;

    Window(const char* title, int width, int height);

    ~Window();
};

#endif //WINDOW_H
