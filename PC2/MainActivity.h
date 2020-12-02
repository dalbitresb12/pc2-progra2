#pragma once

#include "Game.h"

namespace PC2 {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  public ref class MainActivity : public System::Windows::Forms::Form {
    Graphics^ graficador;
    BufferedGraphics^ buffer;
    Game^ game;
    System::Windows::Forms::Timer^ movementTimer;
    System::ComponentModel::IContainer^ components;

  public:
    MainActivity() {
      InitializeComponent();
      this->graficador = CreateGraphics();
      this->graficador->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
      this->buffer = BufferedGraphicsManager::Current->Allocate(this->graficador, this->ClientRectangle);
      this->game = gcnew Game();
    }

  protected:
    ~MainActivity() {
      if (components) {
        delete components;
      }
      delete this->buffer;
      delete this->graficador;
      delete this->game;
    }
  private:
#pragma region Windows Form Designer generated code
    void InitializeComponent(void) {
      this->components = (gcnew System::ComponentModel::Container());
      this->movementTimer = (gcnew System::Windows::Forms::Timer(this->components));
      this->SuspendLayout();
      // 
      // movementTimer
      // 
      this->movementTimer->Enabled = true;
      this->movementTimer->Interval = 20;
      this->movementTimer->Tick += gcnew System::EventHandler(this, &MainActivity::Movement_Tick);
      // 
      // MainActivity
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1088, 554);
      this->MaximumSize = System::Drawing::Size(1104, 593);
      this->MinimumSize = System::Drawing::Size(1104, 593);
      this->Name = L"MainActivity";
      this->Text = L"New Gunbound";
      this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainActivity::MainActivity_FormClosing);
      this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainActivity::MainActivity_KeyDown);
      this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MainActivity::MainActivity_KeyUp);
      this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MainActivity::MainActivity_MouseDown);
      this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MainActivity::MainActivity_MouseMove);
      this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MainActivity::MainActivity_MouseUp);
      this->ResumeLayout(false);

    }
#pragma endregion

  private: System::Void MainActivity_KeyDown(Object^ sender, KeyEventArgs^ e) {
    this->game->MovePlayer(true, e->KeyCode);
  }

  private: System::Void MainActivity_KeyUp(Object^ sender, KeyEventArgs^ e) {
    this->game->MovePlayer(false, e->KeyCode);
  }

  private: System::Void Movement_Tick(Object^ sender, EventArgs^ e) {
    this->game->CheckCollisions();
    this->game->DrawGame(buffer->Graphics, this->ClientRectangle);
    this->buffer->Render();
  }

  private: System::Void MainActivity_MouseMove(Object^ sender, MouseEventArgs^ e) {
    this->game->MouseMove(sender, e);
  }
  private: System::Void MainActivity_MouseUp(Object^ sender, MouseEventArgs^ e) {
    this->game->MouseUp(sender, e);
  }
  private: System::Void MainActivity_MouseDown(Object^ sender, MouseEventArgs^ e) {
    this->game->MouseDown(sender, e);
  }

  public: System::Void PrepareGame(PlayerType type, int bullets) {
    this->game->SetPlayer(this->game->CreatePlayer(type, bullets));
  }

  private: System::Void MainActivity_FormClosing(Object^ sender, FormClosingEventArgs^ e) {
    Application::Exit();
  }
  };
}
