#include "StartScreen.h"
#include <Graphics\Graphics.h>
#include <InputManager\InputManager.h>
#include <StateManager\StateManager.h>
#include <System\System.h>

StartScreen::StartScreen() : TileLevel("")
{
  screenId = GraphicsRender->AddTexture("IntroScreen.png");
}

void StartScreen::Update(float dt)
{
  GraphicsRender->SetTexture(screenId);
  GraphicsRender->DrawTexturedRect(0,0,600,800);
  GraphicsRender->SetCameraPosition(0,0);

  if(InputManager::AnyKeyInput())
  {
    System::stateManager->NextLevel();
  }

}
