#include "Level.h"
#include <fstream>
#include <sstream>
#include <Graphics\Graphics.h>

TileLevel::TileLevel(std::string level)
{
  std::ifstream file(level);

  if(file)
  {
    std::string line;
    int x = 0;
    int y = 0;

    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        int num;
        while(linestream.good())
        {
          linestream >> num;

          if(num == TILE_PLAYER)
          {

            continue;
          }

          Tile tile;
          tile.data = (TileData)num;
          tile.x = x;
          tile.y = y;
          tiles.push_back(tile);

          x++;
        }
        y++;
        x = 0;
    }
  }
  GraphicsRender->SetCameraPosition(100,-100);
}

static const int w = 32;
static const int h = 32;

void TileLevel::Update(float dt)
{
  for(auto it = tiles.begin(); it != tiles.end(); ++it)
  {
    if(it->data == TILE_SOLID)
      GraphicsRender->SetColor(255,0,0,255);
    if(it->data == TILE_AIR)
      GraphicsRender->SetColor(0,0,0,0);

    GraphicsRender->DrawRect(it->x * w,-it->y * h,h,w);
  }
}