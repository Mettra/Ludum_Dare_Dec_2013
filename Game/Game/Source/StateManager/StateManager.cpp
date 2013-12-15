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

      if(glfwGetKey(System::window,GLFW_KEY_R))
        nextState = STATE_RELOAD;

      level->Update(0.016);

      for(auto it = gameObjectList->begin(); it != gameObjectList->end(); ++it)
      {
        (*it)->Update(0.016);
      }

      GraphicsRender->EndRender();
    }

    delete level;
    level = 0;

    for(auto it = gameObjectList->begin(); it != gameObjectList->end(); ++it)
    {
      delete *it;
    }
    gameObjectList->clear();

    if(nextState == STATE_RELOAD)
    {
      nextState = STATE_NEWLEVEL;
    }

    prevState = state;
    state = nextState;
  }
}