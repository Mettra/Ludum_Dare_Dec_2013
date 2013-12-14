#include "Collision.h"
#include <System\Level.h>
#include <System\System.h>
#include <StateManager\StateManager.h>

bool GetTileData(Tile **tileMap,int width, int height,float xF,float yF)
{
  int x = (int)std::floor(xF + 0.5);
  int y = (int)std::floor(yF + 0.5);

  if(x < 0 || x >= width || y < 0 || y >= height)
    return false;

  return tileMap[x][y].data == TILE_SOLID;
}

int DetectCollision(float x, float y,float width, float height)
{
  Tile **tileMap = System::stateManager->GetLevel()->GetTileMap();
  int TileWidth = System::stateManager->GetLevel()->Width();
  int TileHeight = System::stateManager->GetLevel()->Height();

  int ret = 0;
  float x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7,x8,y8;

  //Hotspot 1 Bot Left
  x1 = x - width / 2;
  y1 = y - height / 4;

  //Hotspot 2 Top Left
  x2 = x - width / 2;
  y2 = y + height / 4;

  //Hotspot 3 Top Right
  x3 = x + width / 2;
  y3 = y - height / 4;

  //Hotspot 4 Bot Right
  x4 = x + width / 2;
  y4 = y + height / 4;

  //Hotspot 5 Left Bot
  x5 = x - width / 4;
  y5 = y - height / 2;

  //Hotspot 6 Right Bot
  x6 = x + width / 4;
  y6 = y - height / 2;

  //Hotspot 7 Left Top
  x7 = x - width / 4;
  y7 = y + height / 2;

  //Hotspot 8 Right Top
  x8 = x + width / 4;
  y8 = y + height / 2;

  if(GetTileData(tileMap,TileWidth,TileHeight,x1,y1) || GetTileData(tileMap,TileWidth,TileHeight,x2,y2))
  {
    ret |= COLLISION_LEFT;
  }

  if(GetTileData(tileMap,TileWidth,TileHeight,x3,y3) || GetTileData(tileMap,TileWidth,TileHeight,x4,y4))
  {
    ret |= COLLISION_RIGHT;
  }

  if(GetTileData(tileMap,TileWidth,TileHeight,x5,y5) || GetTileData(tileMap,TileWidth,TileHeight,x6,y6))
  {
    ret |= COLLISION_BOTTOM;
  }

  if(GetTileData(tileMap,TileWidth,TileHeight,x7,y7) || GetTileData(tileMap,TileWidth,TileHeight,x8,y8))
  {
    ret |= COLLISION_TOP;
  }

  return ret;
}