#pragma once

#include <string>
#include <vector>


struct Color
{
  typedef unsigned char uchar;
  Color(uchar r = 0, uchar g = 0, uchar b = 0,uchar a = 0) : r(r),g(g),b(b),a(a) {}
  unsigned r;
  unsigned g;
  unsigned b;
  unsigned a;

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
  TILE_CHECKPOINT_BASE,
  TILE_CHECKPOINT_TOP,
  TILE_CHECKPOINT,
  TILE_CHECKPOINT_HORIZ,
  TILE_CHECKPOINT_LEFT,
  TILE_CHECKPOINT_RIGHT,
  TILE_NEXT_LEVEL,
  TILE_BUTTON,
  TILE_MESSAGE_1,
  TILE_MESSAGE_2,
  TILE_PLAYER = 99
};

struct Tile
{
  Tile(TileData data = TILE_AIR,bool solid = false) : data(data),solid(solid) {}
  TileData data;
  int x;
  int y;
  int aValue;
  bool solid;
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
  Tile HandleColor(Color c);
  void ResetClick();

private:
  int width;
  int height;
  bool usedClick;
  Tile PrevTile;

  unsigned tileId;
  unsigned checkPointId;
  unsigned checkPointTop;
  unsigned beamId;

  unsigned beamIdHoriz;
  unsigned checkPointLeft;
  unsigned checkPointRight;

  std::vector<std::pair<Color,Tile>> colorMatch;

  Tile **tileMap;
};