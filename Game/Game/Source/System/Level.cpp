#include "Level.h"
#include <fstream>
#include <sstream>
#include <Graphics\Graphics.h>
#include <GameObjects\Factory.h>
#include <System\System.h>
#include <GameObjects\TextureObject.h>
#include <GameObjects\Player.h>

struct Bitmap
{
  Bitmap() : width(0),height(0),bitmap(0) {}
  int width;
  int height;
  Color **bitmap;
};

typedef unsigned int uint;
typedef unsigned short ushort;

#pragma pack(push, 1)

typedef struct BITMAPFILEHEADER
{
    char signature[2];  //specifies the file type
    int fileSize;  //specifies the size in bytes of the bitmap file
    char reserved[4];  //reserved; must be 0
    int offset;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
};

#pragma pack(pop)

#pragma pack(push, 1)

typedef struct BITMAPINFOHEADER
{
    unsigned int size;
    int width;
    int height;
    short planes;
    short bitCount;
    unsigned int compression;
    unsigned int imageSize;
    int horizRes;
    int vertRes;
    unsigned int colors;
    unsigned int importantColors;
};

#pragma pack(pop)

Bitmap ReadImage(std::string filename)
{
  Bitmap bitmap;
  BITMAPINFOHEADER infoheader;
  BITMAPFILEHEADER fileheader;

  FILE *file = fopen(filename.c_str(),"rb");
  if(file)
  {
    //read the bitmap file header
    fread(&fileheader.signature,   sizeof(fileheader.signature),1,file);
    fread(&fileheader.fileSize,    sizeof(char) * 4            ,1,file);
    fread(&fileheader.reserved,    sizeof(fileheader.reserved) ,1,file);
    fread(&fileheader.offset,      sizeof(char) * 4            ,1,file);

    //verify that this is a bmp file by check bitmap id
    if (fileheader.signature[0] != 'B' || fileheader.signature[1] != 'M')
    {
        fclose(file);
        return bitmap;
    }

    fread(&infoheader.size,            sizeof(char) * 4,1,file);
    fread(&infoheader.width,           sizeof(char) * 4,1,file);
    fread(&infoheader.height,          sizeof(char) * 4,1,file);
    fread(&infoheader.planes,          sizeof(char) * 2,1,file);
    fread(&infoheader.bitCount,        sizeof(char) * 2,1,file);
    fread(&infoheader.compression,     sizeof(char) * 4,1,file);
    fread(&infoheader.imageSize ,      sizeof(char) * 4,1,file);
    fread(&infoheader.horizRes,        sizeof(char) * 4,1,file);
    fread(&infoheader.vertRes,         sizeof(char) * 4,1,file);
    fread(&infoheader.colors,          sizeof(char) * 4,1,file);
    fread(&infoheader.importantColors, sizeof(char) * 4,1,file);

    int size = infoheader.width*infoheader.height*(infoheader.bitCount>>3);
    unsigned char *data = new unsigned char[size];
    memset(data,0,size * sizeof(unsigned char));

    fseek(file,fileheader.offset,SEEK_SET);
    fread(data,sizeof(unsigned char),size,file);
    fclose(file);

    bitmap.width = infoheader.width;
    bitmap.height = infoheader.height;
    bitmap.bitmap = new Color*[bitmap.width];
    for(int i = 0; i < bitmap.width; ++i)
    {
      bitmap.bitmap[i] = new Color[bitmap.height];
    }

    int offset = 0;
    for(int j = 0; j < bitmap.height; ++j)
    {
      for(int i = 0; i < bitmap.width; ++i)
      {
        bitmap.bitmap[i][j].b = data[offset];
        bitmap.bitmap[i][j].g = data[offset + 1];
        bitmap.bitmap[i][j].r = data[offset + 2];
        bitmap.bitmap[i][j].a = data[offset + 3];
        offset += 4;
      }
    }

    delete [] data;
  }

  return bitmap;
}

Tile TileLevel::HandleColor(Color c)
{
  for(auto it = colorMatch.begin(); it != colorMatch.end(); ++it)
  {
    if(it->first == c)
    {
      it->second.aValue = c.a;
      return it->second;
    }
  }

  return Tile();
}

TileLevel::TileLevel(std::string level)
{
  colorMatch.push_back(std::make_pair(Color(0  ,0  ,0)  , Tile(TILE_SOLID                 ,true ) ));
  colorMatch.push_back(std::make_pair(Color(255,255,255), Tile(TILE_AIR                   ,false) ));
  colorMatch.push_back(std::make_pair(Color(0,  255,0)  , Tile(TILE_PLAYER                ,false) ));
  colorMatch.push_back(std::make_pair(Color(255,255,0)  , Tile(TILE_CHECKPOINT            ,false) ));
  colorMatch.push_back(std::make_pair(Color(200,255,0)  , Tile(TILE_CHECKPOINT_HORIZ      ,false) ));
  colorMatch.push_back(std::make_pair(Color(200,200,0)  , Tile(TILE_CHECKPOINT_BASE       ,true ) ));
  colorMatch.push_back(std::make_pair(Color(100,100,0)  , Tile(TILE_CHECKPOINT_TOP        ,true ) ));
  colorMatch.push_back(std::make_pair(Color(150,200,0)  , Tile(TILE_CHECKPOINT_LEFT       ,true ) ));
  colorMatch.push_back(std::make_pair(Color(100,200,0)  , Tile(TILE_CHECKPOINT_RIGHT      ,true ) ));
  colorMatch.push_back(std::make_pair(Color(0  ,0  ,255), Tile(TILE_MESSAGE_1             ,false) ));
  colorMatch.push_back(std::make_pair(Color(0  ,0  ,254), Tile(TILE_MESSAGE_2             ,false) ));
  colorMatch.push_back(std::make_pair(Color(0  ,255,255), Tile(TILE_NEXT_LEVEL            ,false) ));
  colorMatch.push_back(std::make_pair(Color(0  ,100,0  ), Tile(TILE_BUTTON                ,true ) ));

  Bitmap image = ReadImage(level);

  usedClick = false;
  width = image.width;
  height = image.height;

  tileMap = new Tile*[width];
  for(int i = 0; i < width; ++i)
  {
    tileMap[i] = new Tile[height];
  }

  for(int x = 0; x < image.width; x++)
  {
    for(int y = 0; y < image.height; y++)
    {
      Color c = image.bitmap[x][y];
      Tile tile = HandleColor(c);

      int num = tile.data;
      if(num == TILE_PLAYER)
      {
        Player *obj = (Player *)GameObjectFactory::CreateObject("Player");
        obj->Load("guy.png");
        obj->SetPosition((float)x,(float)y);
        tile.data = TILE_AIR;
      }
      else if(num == TILE_MESSAGE_1)
      {
        TextureObject *obj = (TextureObject *)GameObjectFactory::CreateObject("TextureObject");
        obj->SetPosition((float)x + 0.5,(float)y + 0.5);
        obj->Load("sign1.png");
        obj->height = 128;
        obj->width = 512;
      }
      else if(num == TILE_BUTTON)
      {
        TextureObject *obj = (TextureObject *)GameObjectFactory::CreateObject("TextureObject");
        obj->SetPosition((float)x + 0.5,(float)y + 0.5);
        obj->Load("guy.png");
        obj->height = 128;
        obj->width = 512;
      }

      tile.x = x;
      tile.y = y;

      tileMap[x][y] = tile;
    }
  }
  delete [] image.bitmap;
    
  tileId = GraphicsRender->GetCurrentId();
  GraphicsRender->AddTexture("block.png",tileId);

  checkPointId = GraphicsRender->GetCurrentId();
  GraphicsRender->AddTexture("checkPoint.png",checkPointId);
  
  checkPointTop = GraphicsRender->GetCurrentId();
  GraphicsRender->AddTexture("checkPoint_top.png",checkPointTop);

  beamId = GraphicsRender->GetCurrentId();
  GraphicsRender->AddTexture("beam.png",beamId);

  beamIdHoriz = GraphicsRender->GetCurrentId();
  GraphicsRender->AddTexture("beamHoriz.png",beamIdHoriz);

  checkPointLeft = GraphicsRender->GetCurrentId();
  GraphicsRender->AddTexture("checkPoint_left.png",checkPointLeft);

  checkPointRight = GraphicsRender->GetCurrentId();
  GraphicsRender->AddTexture("checkPoint_right.png",checkPointRight);
  

  GraphicsRender->SetCameraPosition(100,150);
}

TileLevel::~TileLevel()
{
  delete [] tileMap;
}

Tile *TileLevel::GetTile(int x, int y)
{
  if(x >=0 && x < width && y >= 0 && y < height)
  {
    return &tileMap[x][y];
  }
  return 0;
}

static const int w = 32;
static const int h = 32;

void TileLevel::ResetClick()
{
  Tile *tile = GetTile(PrevTile.x,PrevTile.y);

  if(tile != 0)
    *tile = PrevTile;

  usedClick = false;
}

void TileLevel::Update(float dt)
{
  double dx,dy;
  glfwGetCursorPos(System::window,&dx,&dy);

  float camX = GraphicsRender->GetCameraX();
  float camY = GraphicsRender->GetCameraY();

  dx -= 800/2 - camX;
  dy = 600 - dy;
  dy -= 600/2 - camY;
  
  static float sinwave = 0.0f;
  sinwave += dt;

  int tileX = (int)(std::floor((dx / 32) + 0.5f));
  int tileY = (int)(std::floor((dy / 32) + 0.5f));

  bool leftClick = glfwGetMouseButton(System::window,GLFW_MOUSE_BUTTON_1) == GLFW_PRESS;
  bool rightClick = glfwGetMouseButton(System::window,GLFW_MOUSE_BUTTON_2) == GLFW_PRESS;

  if(usedClick == false && (leftClick || rightClick))
  {
    Tile *tile = GetTile(tileX,tileY);
    if(tile != NULL)
    {
      TileData tileData = leftClick ? TILE_SOLID : TILE_AIR;

      if(tile->data != tileData)
      {
        //usedClick = true;
        PrevTile = *tile;

        tile->data = tileData;
        tile->solid = leftClick ? true : false;
      }
    }
  }

  for(int i = 0; i < width; ++i)
  {
    for(int j = 0; j < height; ++j)
    {
      Tile &tile = tileMap[i][j];
      unsigned char r,g,b,a;
      r = g = b = a = 0;
      bool drawTexture = true;

      if(tile.data == TILE_SOLID)
        GraphicsRender->SetTexture(tileId);
      else if(tile.data == TILE_CHECKPOINT_BASE)
        GraphicsRender->SetTexture(checkPointId);
      else if(tile.data == TILE_CHECKPOINT_TOP)
        GraphicsRender->SetTexture(checkPointTop);
      else if(tile.data == TILE_CHECKPOINT)
        GraphicsRender->SetTexture(beamId);
      else if(tile.data == TILE_CHECKPOINT_HORIZ)
        GraphicsRender->SetTexture(beamIdHoriz);
      else if(tile.data == TILE_CHECKPOINT_LEFT)
        GraphicsRender->SetTexture(checkPointLeft);
      else if(tile.data == TILE_CHECKPOINT_RIGHT)
        GraphicsRender->SetTexture(checkPointRight);

      if(tile.data == TILE_AIR || tile.data == TILE_NEXT_LEVEL)
        drawTexture = false;

      if(usedClick == false && tileX == i && tileY == j)
      {
        float val = std::max(0.0f,(sin(sinwave * 3) + 2.0f) / 3.0f * 100.0f);
        unsigned char value = (unsigned char)std::min(255.0f,val);

        r = std::min(255,r + value);
        g = std::min(255,g + value);
        b = std::min(255,b + value);
        a = std::min(255,a + value);
      }

      GraphicsRender->SetColor(r,g,b,a);
      if(drawTexture)
        GraphicsRender->DrawTexturedRect((float)tile.x * 32,(float)tile.y * 32.0f,(float)h,(float)w);
      else
        GraphicsRender->DrawRect((float)tile.x * 32,(float)tile.y * 32.0f,(float)h,(float)w);
    }
  }
}