//
// Created by Mat on 02.10.2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "Window.h"
#include "Circle.h"
#include "planet.h"
#include "Rectangle.h"

class Renderer {
public:
    SDL_Renderer* renderer_;

    explicit Renderer(const Window& window);

    ~Renderer() {
        SDL_DestroyRenderer(renderer_);
    }

    //drawing methods
    void DrawCircle(const Circle& circle) const;
    void DrawPlanet(const Planet& planet) const;
    void DrawRectangle(const Rectangle& rect) const;


    void ClearScreen() const {
        SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
        SDL_RenderClear(renderer_);
    }

    void Present() const {
        SDL_RenderPresent(renderer_);
    }

    void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const {
        SDL_SetRenderDrawColor(renderer_, r, g, b, a);
    }
};


#endif //RENDERER_H
