#pragma once
#include "Factory.h"
#include <System\Level.h>

class Button : public GameObject
{
public:
  Button() : isInit(false) {}
  void Update(float dt);
  void Load(std::string const &filename);
  void GetTiles();

  int width;
  int height;

private:
  bool isInit;
  unsigned int texture;
  std::vector<Tile> tiles;
};