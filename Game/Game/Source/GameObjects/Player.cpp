#include "Player.h"
#include <Graphics\Graphics.h>
#include <System\System.h>
#include "Collision.h"
#include <InputManager/InputManager.h>

static const int maxVel = 10.0f;

float SnapToCell(float val)
{
  return (int)(val) + 0.5f;
}

void Player::Update(float dt)
{
  if(InputManager::IsKeyPressed(GLFW_KEY_D))
  {
    if(velX < maxVel)
      velX += maxVel / 10;
  }
  if(InputManager::IsKeyPressed(GLFW_KEY_A))
  {
    if(velX > -maxVel)
      velX -= maxVel / 10;
  }
  if(InputManager::IsKeyPressed(GLFW_KEY_W))
  {
    velY = 5.0f;
  }

  float tempX = x;
  float tempY = y;

  velY -= 0.5f;
  velX *= 0.8;

  tempX += velX * dt;
  tempY += velY * dt;

  int collision = DetectCollision(tempX,tempY,1,1);
  if(collision & COLLISION_BOTTOM || collision & COLLISION_TOP)
  {
    velY = 0;
    tempY = (int)std::floor(tempY + 0.5f);
  }
  if(collision & COLLISION_LEFT || collision & COLLISION_RIGHT)
  {
    velX = 0;
    tempX = (int)std::floor(tempX + 0.5f);
  }

  x = tempX;
  y = tempY;

  GraphicsRender->SetColor(0,255,0,255);
  GraphicsRender->DrawRect(x * 32,y * 32,32,32);
}

ADD_GAMEOBJECT(Player);