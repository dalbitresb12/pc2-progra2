#include "pch.h"
#include "WindowSelection.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace PC2;

int main() {
  std::srand(time(NULL));

  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  Application::Run(gcnew WindowSelection);
  return 0;
}
