#include "Factory.h"

class Player : public GameObject
{
public:
  Player() : velX(0),velY(0) {}
  void Update(float dt);

private:
  float velX;
  float velY;
};