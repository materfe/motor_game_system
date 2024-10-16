//
// Created by Mat on 02.10.2024.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "window.h"
#include "circle.h"
#include "planet.h"
#include "rectangle.h"

class Renderer {
 private :
  SDL_Renderer *renderer_;

  void RenderDraw(int x, int y) const;
  void TestDrawCircle(int center_x, int center_y, int radius) const;
  void FillCircle(int center_x, int center_y, int radius) const;
 public:

  explicit Renderer(const Window &window);

  ~Renderer() {
    SDL_DestroyRenderer(renderer_);
  }

  //drawing methods
  void DrawCircle(const Circle &circle) const;
  void DrawRectangle(const Rectangle &rect) const;
  void DrawCornersOfPlanet(const Planet &planet) const;
  void DrawFullPlanet(int center_x, int center_y, int radius) const;

  void ClearScreen() const;

  void Present() const { SDL_RenderPresent(renderer_); }

  void SetDrawColor(const Uint8 r,
                    const Uint8 g,
                    const Uint8 b,
                    const Uint8 a) const { SDL_SetRenderDrawColor(renderer_, r, g, b, a); }
};

#endif //RENDERER_H
