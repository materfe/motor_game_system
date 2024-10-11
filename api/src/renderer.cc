//
// Created by Mat on 02.10.2024.
//

#include "renderer.h"
#include <iostream>

renderer::renderer(window &window) {
    renderer_ = SDL_CreateRenderer(window.window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == nullptr) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window.window_);
        SDL_Quit();
        exit(1);
    }
}

//drawing mathods
void renderer::DrawRectangle(const rectangle &rect) const {
    const SDL_Rect sdlRect = { rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight() };
    SDL_RenderFillRect(renderer_, &sdlRect);
}
void renderer::DrawCircle(const circle &circle) const {
    int offsetX = 0;
    int offsetY = circle.getRadius();
    int d = 1 - circle.getRadius();

    auto DrawPixel = [this](int x, int y) {
        SDL_RenderDrawPoint(renderer_, x, y);
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
