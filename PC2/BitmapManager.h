#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Collections::Generic;

ref class BitmapManager {
  Dictionary<String^, Bitmap^>^ images;

public:
  BitmapManager() {
    this->images = gcnew Dictionary<String^, Bitmap^>();
  }
  ~BitmapManager() {
    for each (KeyValuePair<String^, Bitmap^> img in this->images) {
      if (img.Value != nullptr)
        delete img.Value;
      delete img.Key;
    }
    this->images->Clear();
    delete this->images;
  }

  bool HasImage(String^ path) {
    return this->images->ContainsKey(path);
  }

  bool HasImage(Bitmap^ bmp) {
    return this->images->ContainsValue(bmp);
  }

  void PreloadImage(String^ path) {
    if (!this->images->ContainsKey(path)) {
      Bitmap^ bmp = this->LoadImage(path);
      this->images->Add(path, bmp);
    }
  }

  void ReleaseImage(String^ path) {
    Bitmap^ bmp;
    if (this->images->TryGetValue(path, bmp)) {
      images->Remove(path);
      delete bmp;
    }
  }

  Bitmap^ GetImage(String^ path) {
    Bitmap^ bmp;
    if (!this->images->TryGetValue(path, bmp)) {
      bmp = this->LoadImage(path);
      this->images->Add(path, bmp);
    }
    return bmp;
  }

private:
  Bitmap^ LoadImage(String^ path) {
    Bitmap^ bmp = gcnew Bitmap(path);
    return bmp;
  }
};
