#include "Factory.h"

GameObjectFactory *GameObjectFactory::factoryHead = 0;
std::vector<GameObject *> *gameObjectList;

GameObjectFactory::GameObjectFactory(std::string name, CreateFunc func) : name(name),create(func)
{
  next = factoryHead;
  factoryHead = this;
}

GameObject *GameObjectFactory::CreateObject(std::string name)
{
  GameObjectFactory *iter = factoryHead;
  while(iter != 0)
  {
    if(iter->name == name)
    {
      GameObject *obj = iter->create();
      gameObjectList->push_back(obj);
      return obj;
    }
  }

  return 0;
}