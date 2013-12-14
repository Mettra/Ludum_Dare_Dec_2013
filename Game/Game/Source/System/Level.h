#include <string>
#include <vector>

enum TileData
{
  TILE_AIR,
  TILE_SOLID,
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