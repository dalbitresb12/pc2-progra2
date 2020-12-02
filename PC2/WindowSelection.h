#pragma once

#include "MainActivity.h"
#include "Player.h"

namespace PC2 {

  using namespace System;
  using namespace System::ComponentModel;
  using namespace System::Collections;
  using namespace System::Windows::Forms;
  using namespace System::Data;
  using namespace System::Drawing;

  /// <summary>
  /// Summary for WindowSelection
  /// </summary>
  public ref class WindowSelection : public System::Windows::Forms::Form {
  public:
    WindowSelection(void) {
      InitializeComponent();
      //
      //TODO: Add the constructor code here
      //
    }

  protected:
    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    ~WindowSelection() {
      if (components) {
        delete components;
      }
    }
  private: System::Windows::Forms::Button^ startBtn;
  private: System::Windows::Forms::GroupBox^ groupBox1;
  private: System::Windows::Forms::RadioButton^ playerTwoRadio;

  private: System::Windows::Forms::RadioButton^ playerOneRadio;

  private: System::Windows::Forms::NumericUpDown^ pewPewsNum;

  private: MainActivity^ mainWindow;


  private: System::Windows::Forms::Label^ label1;
  protected:

  protected:

  protected:

  private:
    /// <summary>
    /// Required designer variable.
    /// </summary>
    System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    void InitializeComponent(void) {
      System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(WindowSelection::typeid));
      this->startBtn = (gcnew System::Windows::Forms::Button());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->playerTwoRadio = (gcnew System::Windows::Forms::RadioButton());
      this->playerOneRadio = (gcnew System::Windows::Forms::RadioButton());
      this->pewPewsNum = (gcnew System::Windows::Forms::NumericUpDown());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->groupBox1->SuspendLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pewPewsNum))->BeginInit();
      this->SuspendLayout();
      // 
      // startBtn
      // 
      this->startBtn->Location = System::Drawing::Point(223, 292);
      this->startBtn->Name = L"startBtn";
      this->startBtn->Size = System::Drawing::Size(200, 23);
      this->startBtn->TabIndex = 0;
      this->startBtn->Text = L"Pew-pew!";
      this->startBtn->UseVisualStyleBackColor = true;
      this->startBtn->Click += gcnew System::EventHandler(this, &WindowSelection::startBtn_Click);
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->playerTwoRadio);
      this->groupBox1->Controls->Add(this->playerOneRadio);
      this->groupBox1->Location = System::Drawing::Point(223, 187);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(200, 73);
      this->groupBox1->TabIndex = 1;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Pew-pewer";
      // 
      // playerTwoRadio
      // 
      this->playerTwoRadio->AutoSize = true;
      this->playerTwoRadio->Location = System::Drawing::Point(6, 42);
      this->playerTwoRadio->Name = L"playerTwoRadio";
      this->playerTwoRadio->Size = System::Drawing::Size(101, 17);
      this->playerTwoRadio->TabIndex = 1;
      this->playerTwoRadio->TabStop = true;
      this->playerTwoRadio->Text = L"Red Pew-pewer";
      this->playerTwoRadio->UseVisualStyleBackColor = true;
      // 
      // playerOneRadio
      // 
      this->playerOneRadio->AutoSize = true;
      this->playerOneRadio->Checked = true;
      this->playerOneRadio->Location = System::Drawing::Point(6, 19);
      this->playerOneRadio->Name = L"playerOneRadio";
      this->playerOneRadio->Size = System::Drawing::Size(102, 17);
      this->playerOneRadio->TabIndex = 0;
      this->playerOneRadio->TabStop = true;
      this->playerOneRadio->Text = L"Blue Pew-pewer";
      this->playerOneRadio->UseVisualStyleBackColor = true;
      // 
      // pewPewsNum
      // 
      this->pewPewsNum->Location = System::Drawing::Point(343, 266);
      this->pewPewsNum->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {
        15, 0, 0, 0
      });
      this->pewPewsNum->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {
        1, 0, 0, 0
      });
      this->pewPewsNum->Name = L"pewPewsNum";
      this->pewPewsNum->Size = System::Drawing::Size(80, 20);
      this->pewPewsNum->TabIndex = 2;
      this->pewPewsNum->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {
        1, 0, 0, 0
      });
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(226, 268);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(117, 13);
      this->label1->TabIndex = 3;
      this->label1->Text = L"Cantidad de Pew-Pews";
      // 
      // WindowSelection
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
      this->ClientSize = System::Drawing::Size(684, 327);
      this->Controls->Add(this->label1);
      this->Controls->Add(this->pewPewsNum);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->startBtn);
      this->Name = L"WindowSelection";
      this->Text = L"New Gunbound";
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pewPewsNum))->EndInit();
      this->ResumeLayout(false);
      this->PerformLayout();

    }
#pragma endregion
  private: System::Void startBtn_Click(Object^ sender, EventArgs^ e) {
    PlayerType type = playerOneRadio->Checked ? PlayerType::Blue : PlayerType::Red;
    int bullets = (int)pewPewsNum->Value;

    this->Hide();

    if (this->mainWindow == nullptr)
      this->mainWindow = gcnew MainActivity();

    this->mainWindow->PrepareGame(type, bullets);
    this->mainWindow->ShowDialog();
    this->Show();
  }

  };
}
