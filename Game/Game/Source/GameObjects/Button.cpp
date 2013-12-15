#include "Button.h"
#include <Graphics\Graphics.h>
#include <System\System.h>
#include <StateManager\StateManager.h>

static const int alphaOffset = 100;

bool isInVector(std::vector<std::pair<int,int>> const *vector,int x,int y)
{
  for(auto it = vector->begin(); it != vector->end(); ++it)
  {
    if(x == it->first && y == it->second)
      return true;
  }

  return false;
}

void RecursiveTileScan(Tile &currentTile,TileLevel &level,std::vector<Tile> &foundTiles, int searchValue,std::vector<std::pair<int,int>> *oldPosition)
{
  if(searchValue >= alphaOffset)
    foundTiles.push_back(currentTile);

  oldPosition->push_back(std::make_pair(currentTile.x,currentTile.y));

  for(int x = currentTile.x - 1; x <= currentTile.x + 1; x++)
  {
    for(int y = currentTile.y - 1; y <= currentTile.y + 1; y++)
    {
      if( (x == 0 && y == 0) || isInVector(oldPosition,x,y) )
        continue;

      Tile *tile = level.GetTile(x,y);

      if(tile != NULL && tile->aValue != 255 && (tile->aValue == currentTile.aValue || (currentTile.aValue < alphaOffset && tile->aValue == currentTile.aValue + alphaOffset)))
      {
        RecursiveTileScan(*tile,level,foundTiles,tile->aValue,oldPosition);
      }
    }
  }
}

void Button::GetTiles()
{
  Tile *currentTile = System::stateManager->GetLevel()->GetTile(x,y);
  int searchValue = currentTile->aValue;

  std::vector<std::pair<int,int>> oldPositions;

  RecursiveTileScan(*currentTile,*System::stateManager->GetLevel(),tiles,searchValue,&oldPositions);
  isInit = true;
}

void Button::Update(float dt)
{
  if(isInit == false)
  {
    GetTiles();
  }

  Tile *aboveTile = System::stateManager->GetLevel()->GetTile(x,y + 1);
  if(aboveTile->solid == true && active == false)
  {
    active = true;
    for(auto it = tiles.begin(); it != tiles.end(); ++it)
    {
      Tile &curTile = *it;

      Tile *tile = System::stateManager->GetLevel()->GetTile(curTile.x,curTile.y);

      tile->data = curTile.data != TILE_AIR ? TILE_AIR : TILE_SOLID;
      tile->solid = curTile.data != TILE_AIR ? false : true;
    }
  }
  if(aboveTile->solid == false && active == true)
  {
    active = false;
    for(auto it = tiles.begin(); it != tiles.end(); ++it)
    {
      Tile &curTile = *it;

      Tile *tile = System::stateManager->GetLevel()->GetTile(curTile.x,curTile.y);
      tile->data = curTile.data != TILE_AIR ? curTile.data : TILE_AIR;
      tile->solid = curTile.data != TILE_AIR ? curTile.solid : false;
    }
  }
}

void Button::Load(std::string const &filename)
{
  
  texture = GraphicsRender->AddTexture(filename.c_str());
}

ADD_GAMEOBJECT(Button);