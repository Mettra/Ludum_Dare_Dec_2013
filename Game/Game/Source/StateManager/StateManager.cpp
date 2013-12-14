#include "StateManager.h"
#include <System\Level.h>
#include <System\System.h>
#include <GameObjects\Factory.h>

void StateManager::Initialize()
{
  LoadLevel("baselevel.level");
  state = STATE_NEWLEVEL;
}

void StateManager::Update()
{
  while(System::isActive)
  {
    if(state == STATE_NEWLEVEL)
    {
      level = new TileLevel(levelName);
      prevState = state;
      state = STATE_LEVEL;
      nextState = state;
    }

    while(state == nextState)
    {  
      glfwPollEvents();

      GraphicsRender->BeginRender();

      level->Update(0.016);

      for(auto it = gameObjectList->begin(); it != gameObjectList->end(); ++it)
      {
        (*it)->Update(0.016);
      }

      GraphicsRender->EndRender();
    }
  }
}