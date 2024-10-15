//
// Created by Mat on 02.10.2024.
//

#include "renderer.h"
#include <iostream>

Renderer::Renderer(const Window &window) {
    renderer_ = SDL_CreateRenderer(window.window_, -1, SDL_RENDERER_ACCELERATED);
    if (renderer_ == nullptr) {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window.window_);
        SDL_Quit();
        exit(1);
    }
}

//drawing methods
void Renderer::DrawRectangle(const Rectangle &rect) const {
    const SDL_Rect sdlRect = { rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight() };
    SDL_RenderFillRect(renderer_, &sdlRect);
}
void Renderer::DrawCircle(const Circle &circle) const {
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
void Renderer::DrawPlanet(const Planet &planet) const {
    int offsetX = 0;
    int offsetY = static_cast<int>(planet.getRadius());
    int d = 1 - static_cast<int>(planet.getRadius());

    auto DrawPixel = [this](const int x, const int y) {
        SDL_RenderDrawPoint(renderer_, x, y);
    };

    const auto x_in_int = static_cast<int>(planet.getX());
    const auto y_in_int = static_cast<int>(planet.getY());


    auto DrawCirclePoints = [DrawPixel, x_in_int, y_in_int](const int dx, const int dy) {
        DrawPixel(x_in_int - dx, y_in_int + dy);
        DrawPixel(x_in_int + dx, y_in_int - dy);
        DrawPixel(x_in_int - dx, y_in_int - dy);
        DrawPixel(x_in_int + dx, y_in_int + dy);
        DrawPixel(x_in_int + dy, y_in_int + dx);
        DrawPixel(x_in_int - dy, y_in_int + dx);
        DrawPixel(x_in_int + dy, y_in_int - dx);
        DrawPixel(x_in_int - dy, y_in_int - dx);
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

//sf::clear
void Renderer::ClearScreen() const
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}

