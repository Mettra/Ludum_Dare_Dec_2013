#include "Player.h"
#include <Graphics\Graphics.h>
#include <System\System.h>
#include "Collision.h"
#include <StateManager\StateManager.h>
#include <InputManager/InputManager.h>
#include <System\System.h>

static const int maxVel = 10.0f;

float SnapToCell(float val)
{
  return (int)(val) + 0.5f;
}

void Player::Load(std::string const &filename,bool alt)
{
   
  texture = GraphicsRender->AddTexture(filename.c_str());
}

void Player::ResolveCollition()
{
  bool found = false;
  for(int y = 1; y >= -1; y--)
  {
    for(int x = -1; x < 1; ++x)
    {
      int resX = (int)std::floor(this->x + x + 0.5f);
      int resY = (int)std::floor(this->y + y + 0.5f);

      Tile *tile = System::stateManager->GetLevel()->GetTile(resX,resY);
      if(tile && tile->data == TILE_AIR)
      {
        this->x += x;
        this->y += y;
        return;
      }
    }
  }
  
  inBlockCount = 0;
}

void Player::Update(float dt)
{
  if(InputManager::IsKeyPressed(GLFW_KEY_D))
  {
    if(velX < maxVel)
      velX += maxVel / 5;
  }
  if(InputManager::IsKeyPressed(GLFW_KEY_A))
  {
    if(velX > -maxVel)
      velX -= maxVel / 5;
  }
  if(InputManager::IsKeyPressed(GLFW_KEY_W))
  {
    if(canJump)
    {
      velY = 15.0f;
      canJump = false;
    }
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
    tempY = std::floor(tempY + 0.5f);

    if(collision & COLLISION_BOTTOM)
      canJump = true;
  }
  if(collision & COLLISION_LEFT || collision & COLLISION_RIGHT)
  {
    velX = 0;
    tempX = std::floor(tempX + 0.5f);
  }
  if(collision == 0)
  {
    canJump = false;
  }

  x = tempX;
  y = tempY;


  Tile *tile =  System::stateManager->GetLevel()->GetTile(x,y);
  if(tile != NULL)
  {
    if(tile->data == TILE_CHECKPOINT || tile->data == TILE_CHECKPOINT_HORIZ)
      System::stateManager->GetLevel()->ResetClick();
    
    if(tile->solid == true)
    {
      inBlockCount++;
      if(inBlockCount == 10)
        ResolveCollition();
    }
    else
      inBlockCount = 0;

    if(tile->data == TILE_NEXT_LEVEL)
    {
      System::stateManager->NextLevel();
    }
  }

  GraphicsRender->SetTexture(texture);
  GraphicsRender->DrawTexturedRect(x * 32,y * 32,32,32);
  GraphicsRender->SetCameraPosition(x * 32,y * 32);
}

ADD_GAMEOBJECT(Player);