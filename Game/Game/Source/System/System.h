#ifndef SYSTEM_H
#define SYSTEM_H

class System
{
public:
  static void Initialize();
  static void Update();
  static void Destroy();

  static bool isActive;
};

#endif