//
// Created by Mat on 02.10.2024.
//

#include "Renderer.h"
#include <iostream>

Renderer::Renderer(Window &window) {
    renderer = SDL_CreateRenderer(window.window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window.window);
        SDL_Quit();
        exit(1);
    }
}

//drawing mathods
void Renderer::DrawRectangle(const Rectangle &rect) const {
    const SDL_Rect sdlRect = { rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight() };
    SDL_RenderFillRect(renderer, &sdlRect);
}
void Renderer::DrawCircle(const Circle &circle) const {
    int offsetX = 0;
    int offsetY = circle.getRadius();
    int d = 1 - circle.getRadius();

    auto DrawPixel = [this](int x, int y) {
        SDL_RenderDrawPoint(renderer, x, y);
    };

    auto DrawCirclePoints = [DrawPixel, circle](int dx, int dy) {
        DrawPixel(circle.getX() - dx, circle.getY() + dy);
        DrawPixel(circle.getX() + dx, circle.getY() - dy);
        DrawPixel(circle.getX() - dx, circle.getY() - dy);
        DrawPixel(circle.getX() + dx, circle.getY() + dy);
        DrawPixel(circle.getX() + dy, circle.getY() + dx);
        DrawPixel(circle.getX() - dy, circle.getY() + dx);
        DrawPixel(circle.getX() + dy, circle.getY() - dx);
        DrawPixel(circle.getX() - dy, circle.getY() - dx);
    };

    DrawCirclePoints(offsetX, offsetY);

    while (offsetX < offsetY) {
        if (d < 0) {
            d += 2 * offsetX + 3;
        } else {
            d += 2 * (offsetX - offsetY) + 5;
            --offsetY;
        }
        ++offsetX;
        DrawCirclePoints(offsetX, offsetY);
    }
}
