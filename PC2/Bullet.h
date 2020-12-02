#pragma once

#include "Entity.h"

using namespace System;
using namespace System::Drawing;

// Realización de Entity
ref class Bullet : public Entity {
  Brush^ brush;

public:
  Bullet(Point pos, Point direction, Brush^ brush) {
    this->x = pos.X;
    this->y = pos.Y;
    this->dx = direction.X;
    this->dy = direction.Y;
    this->width = this->height = 32;
    this->brush = brush;
  }

  void Move(Graphics^ g) override {
    this->x += dx;
    this->y += dy;
    this->dy += 0.5;
  }

  bool HasCollision(Bitmap^ image) {
    if ((this->x >= 0 && this->x <= image->Width) && (this->y >= 0 && this->y <= image->Height))
      return image->GetPixel(this->x, this->y) == Color::FromArgb(255, 0, 0, 0);
    else
      return false;
  }

  bool HasCollision(Rectangle elem) {
    return elem.IntersectsWith(this->GetDrawingArea());
  }

  void Draw(Graphics^ g) override {
    g->FillEllipse(this->brush, this->GetDrawingArea());
  }
};
