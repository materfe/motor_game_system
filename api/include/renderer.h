//
// Created by Mat on 02.10.2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "window.h"
#include "circle.h"
#include "rectangle.h"

class renderer {
public:
    SDL_Renderer* renderer_;

    explicit renderer(window& window);

    ~renderer() {
        SDL_DestroyRenderer(renderer_);
    }

    //drawing methods
    void DrawCircle(const circle& circle) const;
    void DrawRectangle(const rectangle& rect) const;


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
