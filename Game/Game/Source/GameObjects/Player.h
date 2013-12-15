#include "Factory.h"

class Player : public GameObject
{
public:
  Player() : velX(0),velY(0),canJump(true),inBlockCount(0) {}
  void Update(float dt);
  void ResolveCollition();
  void Load(std::string const &filename,bool alt);

private:
  float velX;
  float velY;
  bool canJump;
  int inBlockCount;
  unsigned int texture;
  unsigned int altTexture;
};