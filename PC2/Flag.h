#pragma once

#include "Entity.h"

// Realización de Entity
ref class Flag : public Entity {
  int idx;

public:
  Flag(Bitmap^ img) {
    this->image = img;
    this->width = img->Width / 3;
    this->height = img->Height;
    this->x = 999;
    this->y = 289 - this->height - 23;
    this->idx = 0;
  }

  void Draw(Graphics^ g) override {
    g->DrawImage(image, this->GetDrawingArea(), this->GetCropArea(), GraphicsUnit::Pixel);
    this->idx = (this->idx + 1) % 3;
  }

  Rectangle GetDrawingArea() override {
    return Rectangle((int)x, (int)y, width * 2, height * 2);
  }

private:
  Rectangle GetCropArea() {
    return Rectangle(idx * width, 0, width, height);
  }
};
