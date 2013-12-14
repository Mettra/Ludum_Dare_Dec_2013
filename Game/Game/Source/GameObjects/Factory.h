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

#define ADD_GAMEOBJECT(Object) \
  GameObject *Create_##Object__(){ return new Object(); }\
  GameObjectFactory factory_##Object(#Object,Create_##Object__);