#include "System/System.h"
#include "System/Meta.h"

#include "Graphics/Graphics.h"

Graphics* GraphicsRender = new Graphics();

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

Graphics* g_glRender = new Graphics;

int main(void)
{
  System::Initialize();
  System::Update();

  //S s;
  //s.thing = 1;
  //s.thing2 = 2;
  //s.info = "Hi!";
  //
  //s.AddMember("dThing",new double());
  //s.GetMember<double>("dThing") = 5.0;
  //
  //std::string thing = s.GetMember<std::string>("info");
  //
  //printf("%s %i %f \n",thing.c_str(),s.GetMember<int>("thing"),s.GetMember<double>("dThing"));
  //
  //
  //getchar();

  return 0;
}