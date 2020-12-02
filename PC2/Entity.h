#pragma once

using namespace System;
using namespace System::Drawing;

ref class Entity abstract { // Clase Padre Entity
protected:
  Bitmap^ image;
  float x, y, dx, dy;
  int width, height;

public:
  Entity() {}

  float GetX() {
    return x;
  }
  float GetY() {
    return y;
  }
  float GetDX() {
    return dx;
  }
  float GetDY() {
    return dy;
  }
  int GetWidth() {
    return width;
  }
  int GetHeigth() {
    return height;
  }
  void SetX(float value) {
    this->x = value;
  }
  void SetY(float value) {
    this->y = value;
  }
  void SetDX(float value) {
    this->dx = value;
  }
  void SetDY(float value) {
    this->dy = value;
  }

  bool PointIsInside(Point point) {
    return (point.X > x && point.X < x + width) && (point.Y > y && point.Y < y + height);
  }

  virtual void Move(Graphics^ g) {
    this->x += dx;
    this->y += dy;
  }

  virtual void Draw(Graphics^ g) {
    g->FillRectangle(Brushes::Black, (float)x, (float)y, (float)width, (float)height);
  }

  virtual Rectangle GetDrawingArea() {
    return Rectangle((int)x, (int)y, width, height);
  }
};
