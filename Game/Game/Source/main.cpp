#include "System/System.h"
#include "System/Meta.h"

#include "Graphics/Graphics.h"

Graphics* GraphicsRender = 0;

struct S : public MetaInterface<S>
{
  int thing;
  int thing2;
  std::string info;
};

META_DEFINE(S)
{
  ADD_MEMBER(thing);
  ADD_MEMBER(thing2);
  ADD_MEMBER(info);
}

int main(void)
{
  GraphicsRender = new Graphics();

  System::Initialize();
  System::Update();

  return 0;
}