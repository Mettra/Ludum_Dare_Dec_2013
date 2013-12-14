#pragma once

#include <string>
#include <vector>

enum TileData
{
  TILE_AIR = 0,
  TILE_SOLID = 1,
  TILE_PLAYER = 99
};

struct Tile
{
  TileData data;
  int x;
  int y;
};

class TileLevel
{
public:
  TileLevel(std::string levelName);
  ~TileLevel();
  void Update(float dt);
  Tile **GetTileMap() { return tileMap; }
  int Width() { return width; }
  int Height() { return height; }

private:
  int width;
  int height;

  Tile **tileMap;
};