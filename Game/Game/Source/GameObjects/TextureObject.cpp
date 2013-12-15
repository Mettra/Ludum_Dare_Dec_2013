#include "TextureObject.h"
#include <Graphics\Graphics.h>

void TextureObject::Update(float dt)
{
  GraphicsRender->SetTexture(texture);
  GraphicsRender->DrawTexturedRect(x * 32,y * 32,height,width);
}

void TextureObject::Load(std::string const &filename)
{
  texture = GraphicsRender->AddTexture(filename.c_str());
}

ADD_GAMEOBJECT(TextureObject);