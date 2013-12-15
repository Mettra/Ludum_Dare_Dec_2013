#pragma once
#include "Factory.h"

class TextureObject : public GameObject
{
public:
  void Update(float dt);
  void Load(std::string const &filename);

  int width;
  int height;

private:
  unsigned int texture;
};