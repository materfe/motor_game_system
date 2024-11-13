//
// Created by Mat on 02.10.2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "window.h"
#include "planet.h"
#include "rectangle.h"
#include "physic/physical_circle.h"
#include "physic/physical_polygon.h"

class Renderer {
 private :
  SDL_Renderer *renderer_;

 public:

  explicit Renderer(const Window &window);

  ~Renderer() {
    SDL_DestroyRenderer(renderer_);
  }

  //drawing methods
  void DrawRectangle(const Rectangle &rect) const;
  void DrawCornersOfPlanet(const Planet &planet) const;
  void DrawCornersOfCircle(const PhysicalCircle &circle) const;
  void DrawFullPlanets(const Planet& other_planet) const;
  void DrawFullCircle(const PhysicalCircle &circle, const std::array<uint16_t,3> &color) const;
  void DrawPolygon(const PhysicalPolygon& polygon) const {
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

  void ClearScreen() const;
  void Present() const { SDL_RenderPresent(renderer_); }



  //SET
  void SetDrawColor(const Uint8 r,
                    const Uint8 g,
                    const Uint8 b,
                    const Uint8 a) const { SDL_SetRenderDrawColor(renderer_, r, g, b, a); }
};

#endif //RENDERER_H
