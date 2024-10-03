//
// Created by Mat on 02.10.2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "Window.h"
#include "Circle.h"
#include "Rectangle.h"

class Renderer {
public:
    SDL_Renderer* renderer;

    Renderer(Window& window);

    ~Renderer() {
        SDL_DestroyRenderer(renderer);
    }

    //drawing methods
    void DrawCircle(const Circle& circle) const;
    void DrawRectangle(const Rectangle& rect) const;


    void ClearScreen() const {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void Present() const {
        SDL_RenderPresent(renderer);
    }

    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
};


#endif //RENDERER_H
