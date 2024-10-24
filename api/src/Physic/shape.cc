//
// Created by Mat on 22.10.2024.
//


#include "Physic/shape.h"
#include "common.h"

void Shape::SetRandomColor() {
  color_[0] = common::GenerateAnIntNumber(255);
  color_[1] = common::GenerateAnIntNumber(255);
  color_[2] = common::GenerateAnIntNumber(255);
  color_[3] = common::GenerateAnIntNumber(255);
}