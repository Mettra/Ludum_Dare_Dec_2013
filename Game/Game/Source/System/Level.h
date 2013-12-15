#pragma once

#include <string>
#include <vector>


struct Color
{
  typedef unsigned char uchar;
  Color(uchar r = 0, uchar g = 0, uchar b = 0) : r(r),g(g),b(b) {}
  unsigned r;
  unsigned g;
  unsigned b;

  bool operator ==(Color const &rhs)
  {
    if(r == rhs.r && b == rhs.b && g == rhs.g)
      return true;

    return false;
  }
};

enum TileData
{
  TILE_AIR = 0,
  TILE_SOLID = 1,
  TILE_CHECKPOINT,
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
  Tile *GetTile(int x, int y);
  int HandleColor(Color c);
  void ResetClick();

private:
  int width;
  int height;
  bool usedClick;
  Tile PrevTile;

  std::vector<std::pair<Color,TileData>> colorMatch;

  Tile **tileMap;
};