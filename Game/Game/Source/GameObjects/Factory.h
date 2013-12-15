#pragma once

#include <vector>
#include <string>

class GameObject
{
public:
  GameObject() :x(0),y(0) {}
  virtual ~GameObject() {}
  virtual void Update(float dt);
  void SetPosition(float x, float y);
  float X() { return x; }
  float Y() { return y; }

protected:
  float x;
  float y;
};

extern std::vector<GameObject *> *gameObjectList;

class GameObjectFactory
{
public:
  typedef GameObject *(*CreateFunc)();
  GameObjectFactory(std::string name, CreateFunc func);

  static GameObject *CreateObject(std::string name);

private:
  static GameObjectFactory *factoryHead;
  GameObjectFactory *next;
  std::string name;
  CreateFunc create;
};

#define PASTE(x,y) x##y

#define ADD_GAMEOBJECT(Object) \
  GameObject * PASTE(Create , Object)() { return new Object(); }\
  GameObjectFactory PASTE(factory , Object)(#Object,PASTE(Create , Object));