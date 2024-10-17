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
void Renderer::DrawFullPlanets(const Planet& other_planet) const {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  const int num_segments = 5;
  const int num_vertices = num_segments + 2; // center + segments + last point to close the circle
  const int num_indices = num_segments * 3; // each segment forms a triangle

  std::array<SDL_Vertex, num_vertices> vertices{};
  std::array<int, num_indices> indices{};

  float angle_step = 2.0f * PI / num_segments;

  const SDL_Color color = {static_cast<Uint8>(other_planet.getColor()[0]), static_cast<Uint8>(other_planet.getColor()[1]),
                           static_cast<Uint8>(other_planet.getColor()[2]), static_cast<Uint8>(other_planet.getColor()[3])};

  vertices[0] = { {static_cast<float>(other_planet.getX()), static_cast<float>(other_planet.getY())},
                  {color}, {0, 0} };

  // Generate circle vertices
  for (int i = 0; i <= num_segments; ++i)
  {
    float angle = static_cast<float>(i) * angle_step;
    const auto x = static_cast<float>(other_planet.getX() + (other_planet.getRadius() * 0.25) * cosf(angle));
    const auto y = static_cast<float>(other_planet.getY() + (other_planet.getRadius() * 0.25) * sinf(angle));
    vertices[i]= { {x, y}, {color}, {0, 0} };
  }

  // Generate indices
  for (int i = 1; i <= num_segments; ++i)
  {
    indices[i * 3 + 0] = 0;     // center vertex
    indices[i * 3 + 1] = i + 1; // current vertex
    indices[i * 3 + 2] = i + 2; // next vertex (looping back at the end)
  }

  indices[(num_segments - 1) * 3 + 2] = 1;

  // Use SDL_RenderGeometry to draw the circle
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  if (SDL_RenderGeometry(renderer_, nullptr,
                         vertices.data(), static_cast<int>(vertices.size()),
                         indices.data(), static_cast<int>(indices.size())))
  {
    SDL_Log("%s\n", SDL_GetError());
  }
}


//sf::clear
void Renderer::ClearScreen() const
{
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);
}
