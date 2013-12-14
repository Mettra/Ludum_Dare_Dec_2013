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

      level->Update(0);

      for(auto it = gameObjectList->begin(); it != gameObjectList->end(); ++it)
      {
        (*it)->Update(0);
      }

      
      GraphicsRender->EndRender();

      if( glfwWindowShouldClose(System::window) ){
        nextState = STATE_QUIT;
      }
    }

    if(nextState == STATE_QUIT)
      System::isActive = false;
  }

}