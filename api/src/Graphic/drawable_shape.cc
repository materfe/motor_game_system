//
// Created by Mat on 22.10.2024.
//


#include "Graphic/drawable_shape.h"
#include "common.h"

void DrawableShape::SetRandomColor() {
  for(auto& color : color_)
  {
    color = common::GenerateRandomNumber(0, 255);
  }
}