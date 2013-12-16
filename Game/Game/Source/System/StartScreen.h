#include "Level.h"

class StartScreen : public TileLevel
{
public:
  StartScreen();
  virtual void Update(float dt);

private:
  unsigned screenId;
};