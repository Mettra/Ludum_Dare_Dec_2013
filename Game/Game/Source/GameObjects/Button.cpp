#include "Button.h"
#include <Graphics\Graphics.h>
#include <System\System.h>
#include <StateManager\StateManager.h>

void RecursiveTileScan(Tile &currentTile,TileLevel &level,std::vector<Tile> &foundTiles,int searchValue,std::pair<int,int> exclude)
{
  for(int x = currentTile.x - 1; x <= currentTile.x + 1; x++)
  {
    for(int y = currentTile.y - 1; y <= currentTile.y + 1; y++)
    {
      if( (x == 0 && y == 0) || (x == exclude.first && y == exclude.second) )
        continue;

      Tile *tile = level.GetTile(x,y);

      if(tile != NULL && (tile->aValue == currentTile.aValue || tile->aValue >= 50))
      {
        if(searchValue >= 50)
          foundTiles.push_back(*tile);

        RecursiveTileScan(*tile,level,foundTiles,tile->aValue,std::make_pair(x,y));
      }
    }
  }
}

void Button::GetTiles()
{
  Tile *currentTile = System::stateManager->GetLevel()->GetTile(x,y);
  int searchValue = currentTile->aValue;

  RecursiveTileScan(*currentTile,*System::stateManager->GetLevel(),tiles,searchValue,std::make_pair(x,y));
}

void Button::Update(float dt)
{
  if(isInit == false)
  {
    GetTiles();
  }
}

void Button::Load(std::string const &filename)
{
  
  texture = GraphicsRender->AddTexture(filename.c_str());
}

ADD_GAMEOBJECT(Button);