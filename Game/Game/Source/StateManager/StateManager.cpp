#include "StateManager.h"
#include <System\Level.h>
#include <System\System.h>
#include <GameObjects\Factory.h>
#include <InputManager\InputManager.h>

void StateManager::Initialize()
{
  LoadLevel("baselevel.level");
  state = STATE_NEWLEVEL;
}

void StateManager::Update()
{
  
  GraphicsRender->AddTexture("img.png", 1);
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

      InputManager::Update();


      GraphicsRender->BeginRender();

      level->Update(GraphicsRender->GetDt());
        nextState = STATE_RELOAD;

      level->Update(0.016);

      for(auto it = gameObjectList->begin(); it != gameObjectList->end(); ++it)
      {
        (*it)->Update(GraphicsRender->GetDt());
      }

      
      GraphicsRender->EndRender();

      if( glfwWindowShouldClose(System::window) ){
        nextState = STATE_QUIT;
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

    if(nextState == STATE_QUIT)
      System::isActive = false;
  }

}