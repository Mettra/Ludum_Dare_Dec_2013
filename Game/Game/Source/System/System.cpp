#include "System.h"
#include <Lua\Lua.h>
#include <string>
#include <StateManager\StateManager.h>

bool System::isActive = true;

static StateManager *stateManager = 0;

void System::Initialize()
{
  stateManager = new StateManager();
  stateManager->Initialize();
}

void System::Update()
{
  stateManager->Update();
}

void System::Destroy()
{
  delete stateManager;
}