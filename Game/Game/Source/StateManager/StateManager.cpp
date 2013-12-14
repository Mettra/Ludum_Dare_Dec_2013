#include "StateManager.h"
#include <System\Level.h>
#include <System\System.h>

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

      level->Update(0);

      GraphicsRender->EndRender();
    }
  }
}