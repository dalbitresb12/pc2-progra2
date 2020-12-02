#pragma once

#include "Entity.h"
#include "Bullet.h"

enum class PlayerType {
  Blue, Red
};

// Realización de Entity
ref class Player : public Entity {
  Bullet^ bullet; // Agregación de Bullet
  Pen^ linePen;
  Point lineInitialPos, lineFinalPos;
  int n_bullets;
  bool clicked;
  PlayerType type;

public:
  Player(Bitmap^ img, int n_bullets, PlayerType type) {
    this->image = img;
    this->width = img->Width;
    this->height = img->Height;
    this->x = 188 - width / 2;
    this->y = 375 - height;
    this->n_bullets = n_bullets;
    this->linePen = gcnew Pen(Color::Red, 3);
    this->clicked = false;
    this->type = type;
  }

  int GetBullets() {
    return this->n_bullets;
  }

  Bullet^ GetBullet() {
    return this->bullet;
  }

  void DeleteBullet() {
    delete this->bullet;
    this->bullet = nullptr;
  }

  bool WasClicked() {
    return this->clicked;
  }

  Bullet^ CreateBullet() {
    Point pos = Point(this->x, this->y + 20);
    Point direction = Point((this->x - lineFinalPos.X) / 10, (lineFinalPos.Y - this->y) / -10);
    Brush^ brush = type == PlayerType::Blue ? Brushes::Blue : Brushes::Red;
    return gcnew Bullet(pos, direction, brush);
  }

  void Draw(Graphics^ g) override {
    g->DrawImage(this->image, this->GetDrawingArea());

    if (!this->lineInitialPos.IsEmpty && !this->lineFinalPos.IsEmpty && this->PointIsInside(this->lineInitialPos)) {
      g->DrawLine(this->linePen, this->lineInitialPos, this->lineFinalPos);
    }

    if (this->bullet != nullptr) {
      this->bullet->Move(g);
      this->bullet->Draw(g);
    }
  }

  void MouseDown(Point mouseLoc) {
    if (this->bullet != nullptr)
      return;

    if (this->n_bullets <= 0)
      return;

    this->clicked = true;
    this->lineInitialPos = Point(mouseLoc.X, mouseLoc.Y);
  }

  void MouseMove(Point mouseLoc) {
    if (this->lineFinalPos == mouseLoc) return;
    this->lineFinalPos = Point(mouseLoc.X, mouseLoc.Y);
  }

  void MouseUp(Point mouseLoc) {
    this->clicked = false;
    this->lineFinalPos = Point(mouseLoc.X, mouseLoc.Y);
    this->bullet = this->CreateBullet();

    this->lineInitialPos.X = 0;
    this->lineInitialPos.Y = 0;
    this->lineInitialPos.X = 0;
    this->lineInitialPos.Y = 0;
    this->n_bullets -= 1;
  }

  void Move(Graphics^ g) override {
    if (x + dx >= 0 && x + dx + width <= g->VisibleClipBounds.Width) {
      x += dx;
    }
    if (y + dy >= 0 && y + dy + height <= g->VisibleClipBounds.Height) {
      y += dy;
    }
  }
};
