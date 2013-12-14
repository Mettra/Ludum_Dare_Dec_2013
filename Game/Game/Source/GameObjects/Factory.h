#include <vector>

class GameObject
{
public:
  void Update(float dt);

private:

};

extern std::vector<GameObject *> *gameObjectList;



class GameObjectFactory
{
public:



private:
  static GameObjectFactory *factoryHead;
  GameObjectFactory *next;
};

