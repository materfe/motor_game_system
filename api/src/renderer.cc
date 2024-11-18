//
// Created by Mat on 02.10.2024.
//

#include "renderer.h"
#include <iostream>
#include <vector>

Renderer::Renderer(const Window &window) {
  renderer_ = SDL_CreateRenderer(window.window_, -1, SDL_RENDERER_ACCELERATED);
  if (renderer_ == nullptr) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window.window_);
    SDL_Quit();
    exit(1);
  }
}

//drawing method : Rectangle
void Renderer::DrawRectangle(const Rectangle &rect) const {
  const SDL_Rect sdl_rect = {rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight()};
  SDL_RenderFillRect(renderer_, &sdl_rect);
}
//drawing method : Planets
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
void Renderer::DrawFullPlanets(const Planet &other_planet) const {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif

  std::vector<SDL_Vertex> vertices;
  std::vector<int> indices;

  const int num_segments = 100;
  float angle_step = 2.0f * PI / num_segments;

  const SDL_Color color ({static_cast<Uint8>(other_planet.getColor()[0]), static_cast<Uint8>(other_planet.getColor()[1]),
      static_cast<Uint8>(other_planet.getColor()[2]), static_cast<Uint8>(other_planet.getColor()[3])});

  vertices.push_back(SDL_Vertex({other_planet.getX(), other_planet.getY()}, color, {0, 0}));

  // Generate circle vertices
  for (int i = 0; i <= num_segments; ++i)
  {
    float angle = static_cast<float>(i) * angle_step;
    auto x = static_cast<float>(other_planet.getX() + (other_planet.getRadius() * 0.25) * cosf(angle));
    auto y = static_cast<float>(other_planet.getY() + (other_planet.getRadius() * 0.25) * sinf(angle));
    vertices.push_back(SDL_Vertex({x, y}, color, {0, 0}));
  }

  // Generate indices
  for (int i = 1; i <= num_segments; ++i)
  {
    indices.push_back(0); // center vertex
    indices.push_back(i);
    indices.push_back(i + 1);
  }

  // Use SDL_RenderGeometry to draw the circle
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  if (SDL_RenderGeometry(renderer_, nullptr,
                         vertices.data(), static_cast<int>(vertices.size()),
                         indices.data(), static_cast<int>(indices.size())))
  {
    SDL_Log("%s\n", SDL_GetError());
  }
}
//drawing method : Circle
void Renderer::DrawCornersOfCircle(const PhysicalCircle &circle) const {
  int offset_x = 0;
  int offset_y = static_cast<int>(circle.GetRadius());
  int d = 1 - static_cast<int>(circle.GetRadius());

  auto draw_pixel = [this](const int x, const int y) {
    SDL_RenderDrawPoint(renderer_, x, y);
  };

  const auto x_in_int = static_cast<int>(circle.GetPosition().x_);
  const auto y_in_int = static_cast<int>(circle.GetPosition().y_);

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
void Renderer::DrawFullCircle(const PhysicalCircle &circle, const std::array<uint16_t,3> &color) const {
#ifdef TRACY_ENABLE
  ZoneScoped;
#endif
  std::vector<SDL_Vertex> vertices;
  std::vector<int> indices;

  const int num_segments = 100;
  float angle_step = 2.0f * PI / num_segments;

  const auto color_1 = SDL_Color(0, 0, 0, 255);
  const auto color_2 = SDL_Color(color[0], color[1], color[2], 255);

  vertices.push_back(SDL_Vertex({circle.GetPosition().x_, circle.GetPosition().y_}, color_1, {0, 0}));

  // Generate circle vertices
  for (int i = 0; i <= num_segments; ++i)
  {
    float angle = static_cast<float>(i) * angle_step;
    auto x = static_cast<float>(circle.GetPosition().x_ + (circle.GetRadius()) * std::cosf(angle));
    auto y = static_cast<float>(circle.GetPosition().y_ + (circle.GetRadius()) * std::sinf(angle));
    vertices.push_back(SDL_Vertex({x, y}, color_2, {0, 0}));
  }

  // Generate indices
  for (int i = 1; i <= num_segments; ++i)
  {
    indices.push_back(0); // center vertex
    indices.push_back(i);
    indices.push_back(i + 1);
  }

  // Use SDL_RenderGeometry to draw the circle
  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  if (SDL_RenderGeometry(renderer_, nullptr,
                         vertices.data(), static_cast<int>(vertices.size()),
                         indices.data(), static_cast<int>(indices.size())))
  {
    SDL_Log("%s\n", SDL_GetError());
  }
}
//drawing method : Polygon
void Renderer::DrawPolygon(const PhysicalPolygon &polygon, const std::array<uint16_t,3> &color) const {

  SetDrawColor(color[0], color[1], color[2], 255);

  const auto& vertices = polygon.GetVertices();
  const size_t vertexCount = vertices.size();

  // Ensure we have enough vertices to form a polygon
  if (vertexCount < 3) return;

  // Draw each edge from one vertex to the next
  for (size_t i = 0; i < vertexCount; ++i) {
    const auto& start = vertices[i];
    const auto& end = vertices[(i + 1) % vertexCount]; // Wrap around to the first vertex

    SDL_RenderDrawLine(renderer_,
                       static_cast<int>(start.x_), static_cast<int>(start.y_),
                       static_cast<int>(end.x_), static_cast<int>(end.y_));
  }
}
//drawing method : AABB
void Renderer::DrawAABB(const AABB &aabb, const std::array<uint16_t, 3> &color) {
  // Set the draw color
  SetDrawColor(color[0], color[1], color[2], 255);

  // Create a rectangle from the AABB
  SDL_Rect rect = {static_cast<int>(aabb.GetMinX()), static_cast<int>(aabb.GetMinY()),
                   static_cast<int>(aabb.width()), static_cast<int>(aabb.height())};

  // Draw the rectangle outline
  SDL_RenderDrawRect(renderer_, &rect);
  SDL_RenderFillRect(renderer_, &rect);
}

//sf::Clear
void Renderer::ClearScreen() const {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
}
