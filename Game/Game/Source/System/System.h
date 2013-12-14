#ifndef SYSTEM_H
#define SYSTEM_H

#include "Graphics/Graphics.h"

class System
{
public:
  static void Initialize();
  static void Update();

private:
  static GLFWwindow* window;
};

#endif