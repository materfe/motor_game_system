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
  void DrawPolygon(const PhysicalPolygon& polygon, const std::array<uint16_t,3> &color) const;
  void DrawAABB(const AABB &aabb, const std::array<uint16_t,3> &color);

  void ClearScreen() const;
  void Present() const { SDL_RenderPresent(renderer_); }


  //GET
  [[nodiscard]] SDL_Renderer& renderer() const {return *renderer_;}

  //SET
  void SetDrawColor(const Uint8 r,
                    const Uint8 g,
                    const Uint8 b,
                    const Uint8 a) const { SDL_SetRenderDrawColor(renderer_, r, g, b, a); }
};

#endif //RENDERER_H
