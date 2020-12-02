#pragma once

#include "Bullet.h"

using namespace System;
using namespace System::Drawing;

ref class Map {
protected:
  Bitmap^ background;
  Bitmap^ front;
  Bitmap^ collisionMap;

public:
  Map(Bitmap^ background, Bitmap^ front, Bitmap^ collisionMap) {
    this->background = background;
    this->front = front;
    this->collisionMap = collisionMap;
    this->background->MakeTransparent();
  }

  void MakeTransparent(Point point) {
    // PRIMER INTENTO DE HACER CIRCULARES TRANSPARENTES
    /* double xCenter = r.X + r.Width / 2;
    double yCenter = r.Y + r.Height / 2;
    double ratio = 24;
    for (double i = point.X; i < r.Width; ++i) {
      for (double f = point.Y; f < r.Height; ++f) {
        if (std::sqrt(std::pow(point.X - xCenter, 2) + std::pow(point.Y - yCenter, 2)))
          this->front->SetPixel(i, f, Color::Transparent);
      }
    } */

    // SEGUNDO INTENTO DE HACER CIRCULARES TRANSPARENTES
    /* int radio = 24;
    int origen = radio + 1;
    double distance = sqrt(pow(point.X - origen, 2)) + pow(point.Y - origen, 2);
    if (distance <= radio) {
      for (short f = std::max(point.X, 0); f <= std::min(point.X + 48, front->Width); ++f) {
        for (short c = std::max(point.Y, 0); c <= std::min(point.Y + 48, front->Height); ++c) {
          this->front->SetPixel(f, c, Color::Transparent);
        }
      }
    } */
    // NO RESULTÓ, POR LO QUE NOS QUEDAMOS CON CUADRADOS TRANSPARENTES ):

    for (short x = std::max(point.X, 0); x <= std::min(point.X + 64, front->Width); ++x) {
      for (short y = std::max(point.Y, 0); y <= std::min(point.Y + 64, front->Height); ++y) {
        this->front->SetPixel(x, y, Color::Transparent);
      }
    }
  }

  Rectangle GetFrontArea() {
    return Rectangle(0, 0, this->front->Width, this->front->Height);
  }

  Bitmap^ GetFrontBitmap() {
    return this->front;
  }

  Bitmap^ GetCollisionMap() {
    return this->collisionMap;
  }

  void Draw(Graphics^ g, Rectangle drawingArea) {
    g->DrawImage(background, drawingArea);
    g->DrawImage(front, drawingArea);
  }
};
