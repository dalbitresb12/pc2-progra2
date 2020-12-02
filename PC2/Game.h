#pragma once

#include "BitmapManager.h"
#include "Map.h"
#include "Flag.h"
#include "Player.h"
#include "Bullet.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

ref class Game {
  BitmapManager^ bmpManager; // Composición con BitmapManager
  Flag^ flag; // Composición con Flag
  Player^ player; // Composición con Player
  Map^ map; // Composición con Map 
  bool hasWon;

public:
  Game() {
    this->bmpManager = gcnew BitmapManager();
    bmpManager->PreloadImage("assets\\background.png");
    bmpManager->PreloadImage("assets\\map.png");
    bmpManager->PreloadImage("assets\\collision-map.png");
    bmpManager->PreloadImage("assets\\flag.png");

    this->map = this->CreateMap();
    this->flag = this->CreateFlag();
    this->hasWon = false;
  }

  ~Game() {
    delete bmpManager;
    delete map;
    delete flag;
    if (player != nullptr)
      delete player;
  }

  Map^ CreateMap() {
    Bitmap^ bg = bmpManager->GetImage("assets\\background.png");
    Bitmap^ map = bmpManager->GetImage("assets\\map.png");
    Bitmap^ collisions = bmpManager->GetImage("assets\\collision-map.png");
    return gcnew Map(bg, map, collisions);
  }

  Flag^ CreateFlag() {
    return gcnew Flag(bmpManager->GetImage("assets\\flag.png"));
  }

  Player^ CreatePlayer(PlayerType type, int n_bullets) {
    String^ path;
    switch (type) {
    case PlayerType::Blue:
      path = "assets\\player_1.png"; break;
    case PlayerType::Red:
      path = "assets\\player_2.png"; break;
    }
    Bitmap^ playerImage = bmpManager->GetImage(path);
    return gcnew Player(playerImage, n_bullets, type);
  }

  Player^ GetPlayer() {
    return this->player;
  }

  void SetPlayer(Player^ player) { // Dependencia con Player
    this->player = player;
  }

  void MovePlayer(bool trigger, Keys tecla) {
    if (trigger) {
      if (tecla == Keys::W) {
        player->SetDY(-5);
      } else if (tecla == Keys::S) {
        player->SetDY(5);
      } else if (tecla == Keys::D) {
        player->SetDX(5);
      } else if (tecla == Keys::A) {
        player->SetDX(-5);
      }
    } else {
      if (tecla == Keys::W) {
        player->SetDY(0);
      } else if (tecla == Keys::S) {
        player->SetDY(0);
      } else if (tecla == Keys::D) {
        player->SetDX(0);
      } else if (tecla == Keys::A) {
        player->SetDX(0);
      }
    }
  }

  void CheckCollisions() {
    Bullet^ bullet = this->player->GetBullet();

    if (bullet == nullptr)
      return;

    if (bullet->HasCollision(this->flag->GetDrawingArea()))
      hasWon = true;

    if (!bullet->HasCollision(this->map->GetCollisionMap()))
      return;

    this->map->MakeTransparent(Point(bullet->GetX(), bullet->GetY()));
    this->player->DeleteBullet();
  }

  void DrawGame(Graphics^ g, Rectangle drawingArea) {
    if (this->hasWon) {
      g->DrawImage(bmpManager->GetImage("assets\\win.png"), drawingArea);
      return;
    }

    if (this->player->GetBullets() <= 0 && this->player->GetBullet() == nullptr) {
      g->DrawImage(bmpManager->GetImage("assets\\lose.png"), drawingArea);
      return;
    }

    Bullet^ bullet = this->player->GetBullet();
    if (bullet != nullptr) {
      if (bullet->GetX() < 0 || bullet->GetX() > drawingArea.Width || bullet->GetY() > drawingArea.Height) {
        this->player->DeleteBullet();
      }
    }

    this->player->Move(g);
    this->map->Draw(g, drawingArea);
    this->player->Draw(g);
    this->flag->Draw(g);
  }

  void MouseDown(Object^ sender, MouseEventArgs^ e) {
    if (this->player->PointIsInside(Point(e->Location.X, e->Location.Y))) {
      this->player->MouseDown(e->Location);
    }
  }

  void MouseMove(Object^ sender, MouseEventArgs^ e) {
    if (this->player->WasClicked()) {
      this->player->MouseMove(e->Location);
    }
  }
  void MouseUp(Object^ sender, MouseEventArgs^ e) {
    if (this->player->WasClicked()) {
      this->player->MouseUp(e->Location);
    }
  }
};
