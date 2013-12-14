#include "Player.h"
#include <Graphics\Graphics.h>

void Player::Update(float dt)
{
  x += 0.1f;
  GraphicsRender->SetColor(0,255,0,255);
  GraphicsRender->DrawRect(x,y,10,10);
}

ADD_GAMEOBJECT(Player);