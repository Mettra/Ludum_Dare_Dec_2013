#include "Level.h"
#include <fstream>
#include <sstream>
#include <Graphics\Graphics.h>
#include <GameObjects\Factory.h>

TileLevel::TileLevel(std::string level)
{
  std::ifstream file(level);

  width = 0;
  height = 0;
  std::vector<Tile> tiles;

  if(file)
  {
    std::string line;

    file >> width;
    file >> height;

    int x = 0;
    int y = height;

    tileMap = new Tile*[width];
    for(int i = 0; i < width; ++i)
    {
      tileMap[i] = new Tile[height];
    }

    while(std::getline(file, line))
    {
        std::stringstream linestream(line);
        int num;
        while(linestream.good())
        {
          linestream >> num;

          if(num == TILE_PLAYER)
          {
            GameObject *obj = GameObjectFactory::CreateObject("Player");
            obj->SetPosition(x,y);
            
            num = TILE_AIR;
          }

          Tile tile;
          tile.data = (TileData)num;
          tile.x = x;
          tile.y = y;

          tileMap[x][y] = tile;
          x++;
        }
        y--;
        x = 0;
    }
  }

  GraphicsRender->SetCameraPosition(100,150);
}

TileLevel::~TileLevel()
{

}

static const int w = 32;
static const int h = 32;

void TileLevel::Update(float dt)
{
  for(int i = 0; i < width; ++i)
  {
    for(int j = 0; j < height; ++j)
    {
      Tile &tile = tileMap[i][j];
      if(tile.data == TILE_SOLID)
        GraphicsRender->SetColor(255,0,0,255);
      if(tile.data == TILE_AIR)
        GraphicsRender->SetColor(0,0,0,0);
      
      GraphicsRender->DrawRect(tile.x * 32,tile.y * 32,h,w);
    }
  }
}