#include "StateManager.h"
#include <System\Level.h>
#include <System\System.h>
#include <GameObjects\Factory.h>
#include <InputManager\InputManager.h>
#include <GameObjects\Player.h>
#include <GameObjects\TextureObject.h>
#include <System\StartScreen.h>

void StateManager::Initialize()
{
  levels.push_back("level_1.bmp");
  levels.push_back("level_2.bmp");
  levels.push_back("level_3.bmp");
  levelCount = -1;

  state = STATE_START;
}

void StateManager::NextLevel()
{
  levelCount++;
  if(levelCount < levels.size())
  {
    levelName = levels[levelCount];
    LoadLevel(levelName);
  }
  else
  {
    state = STATE_START;
  }
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
    else if(state == STATE_START)
    {
      level = new StartScreen();
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
      if(InputManager::IsKeyPressed(GLFW_KEY_R))
        nextState = STATE_RELOAD;

      for(auto it = gameObjectList->begin(); it != gameObjectList->end(); ++it)
      {
        (*it)->Update(GraphicsRender->GetDt());
      }
      
      GraphicsRender->EndRender();

      if( glfwWindowShouldClose(System::window) ){
        nextState = STATE_QUIT;
      }
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
    

    if(nextState == STATE_QUIT)
      System::isActive = false;
  }

}