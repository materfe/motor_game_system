//
// Created by Mat on 02.10.2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "window.h"
#include "Graphic/drawable_circle.h"
#include "planet.h"
#include "rectangle.h"

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
  void DrawFullPlanets(const Planet& other_planet) const;

  void ClearScreen() const;

  void Present() const { SDL_RenderPresent(renderer_); }

  void SetDrawColor(const Uint8 r,
                    const Uint8 g,
                    const Uint8 b,
                    const Uint8 a) const { SDL_SetRenderDrawColor(renderer_, r, g, b, a); }
};

#endif //RENDERER_H
