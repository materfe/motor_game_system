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
    const SDL_Rect sdl_rect = { rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight() };
    SDL_RenderFillRect(renderer_, &sdl_rect);
}
void Renderer::DrawCircle(const Circle &circle) const {
    int offset_x = 0;
    int offset_y = circle.getRadius();
    int d = 1 - circle.getRadius();

    auto draw_pixel = [this](const int x, const int y) {
        SDL_RenderDrawPoint(renderer_, x, y);
    };

    auto draw_circle_points = [draw_pixel, circle](int dx, int dy) {
        draw_pixel(circle.getX() - dx, circle.getY() + dy);
        draw_pixel(circle.getX() + dx, circle.getY() - dy);
        draw_pixel(circle.getX() - dx, circle.getY() - dy);
        draw_pixel(circle.getX() + dx, circle.getY() + dy);
        draw_pixel(circle.getX() + dy, circle.getY() + dx);
        draw_pixel(circle.getX() - dy, circle.getY() + dx);
        draw_pixel(circle.getX() + dy, circle.getY() - dx);
        draw_pixel(circle.getX() - dy, circle.getY() - dx);
    };

    draw_circle_points(offset_x, offset_y);

    while (offset_x < offset_y) {
        if (d < 0) {
            d += 2 * offset_x + 3;
        } else {
            d += 2 * (offset_x - offset_y) + 5;
            --offset_y;
        }
        ++offset_x;
        draw_circle_points(offset_x, offset_y);
    }
}
void Renderer::DrawCornersOfPlanet(const Planet &planet) const {
    int offset_x = 0;
    int offset_y = static_cast<int>(planet.getRadius());
    int d = 1 - static_cast<int>(planet.getRadius());

    auto draw_pixel = [this](const int x, const int y) {
        SDL_RenderDrawPoint(renderer_, x, y);
    };

    const auto x_in_int = static_cast<int>(planet.getX());
    const auto y_in_int = static_cast<int>(planet.getY());


    auto draw_circle_points = [draw_pixel, x_in_int, y_in_int](const int dx, const int dy) {
        draw_pixel(x_in_int - dx, y_in_int + dy);
        draw_pixel(x_in_int + dx, y_in_int - dy);
        draw_pixel(x_in_int - dx, y_in_int - dy);
        draw_pixel(x_in_int + dx, y_in_int + dy);
        draw_pixel(x_in_int + dy, y_in_int + dx);
        draw_pixel(x_in_int - dy, y_in_int + dx);
        draw_pixel(x_in_int + dy, y_in_int - dx);
        draw_pixel(x_in_int - dy, y_in_int - dx);
    };

    draw_circle_points(offset_x, offset_y);

    while (offset_x < offset_y) {
        if (d < 0) {
            d += 2 * offset_x + 3;
        } else {
            d += 2 * (offset_x - offset_y) + 5;
            --offset_y;
        }
        ++offset_x;
        draw_circle_points(offset_x, offset_y);
    }
}

//sf::clear
void Renderer::ClearScreen() const
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}





// Function to put a pixel on the screen (helper function for modularity)
void Renderer::RenderDraw(const int x, const int y) const {
  SDL_RenderDrawPoint(renderer_, x, y);
}

// Function to draw a circle using the midpoint circle algorithm
void Renderer::TestDrawCircle(const int center_x, const int center_y, const int radius) const {
  int x = 0;
  int y = radius;
  int d = 1 - radius;  // Decision variable

  // Symmetry of the circle - drawing in all octants
  while (x <= y) {
    // Drawing the 8 symmetric points
    RenderDraw(center_x + x, center_y + y); // Octant 1
    RenderDraw(center_x - x, center_y + y); // Octant 2
    RenderDraw(center_x + x, center_y - y); // Octant 8
    RenderDraw(center_x - x, center_y - y); // Octant 7
    RenderDraw(center_x + y, center_y + x); // Octant 4
    RenderDraw(center_x - y, center_y + x); // Octant 3
    RenderDraw(center_x + y, center_y - x); // Octant 5
    RenderDraw(center_x - y, center_y - x); // Octant 6

    if (d < 0) {
      d += 2 * x + 3;
    } else {
      d += 2 * (x - y) + 5;
      y--;
    }
    x++;
  }
}

// Function to fill the circle by drawing horizontal lines between the points
void Renderer::FillCircle(const int center_x, const int center_y, const int radius) const {
  for (int y = -radius; y <= radius; y++) {
	  const int dx = static_cast<int>(std::sqrt(radius * radius - y * y));
    for (int x = -dx; x <= dx; x++) {
      RenderDraw(center_x + x, center_y + y);
    }
  }
}

// Main draw function, optimized to handle both drawing and filling the circle
void Renderer::DrawFullPlanet(const int center_x, const int center_y, const int radius) const{
  TestDrawCircle(center_x, center_y, radius);    // DrawFullPlanet the outline
  FillCircle(center_x, center_y, radius);    // Fill the circle
}

