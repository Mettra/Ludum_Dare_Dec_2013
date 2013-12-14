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
  void Update(float dt);

private:
  std::vector<Tile> tiles;
};