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

          Tile tile;
          tile.data = (TileData)num;
          tile.x = x;
          tile.y = y;
          tiles.push_back(tile);

          x++;
        }
        y++;
    }
  }
}

void TileLevel::Update(float dt)
{
  for(auto it = tiles.begin(); it != tiles.end(); ++it)
  {
  }
}