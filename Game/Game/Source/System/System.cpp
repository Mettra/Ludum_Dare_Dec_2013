#include "System.h"
#include <Lua\Lua.h>
#include <string>
#include <StateManager\StateManager.h>
#include <GameObjects\Factory.h>
#include <InputManager\InputManager.h>

bool System::isActive = true;
GLFWwindow* System::window = 0;
StateManager *System::stateManager = 0;


void System::Initialize()
{
  stateManager = new StateManager();
  stateManager->Initialize();

  gameObjectList = new std::vector<GameObject *>;

  if (!glfwInit())
    return ;

  window = glfwCreateWindow(800, 600, "A GLFW Example", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return ;
  }
  glfwMakeContextCurrent(window);
  InputManager::Init();

  //Can create graphics now
  GraphicsRender->SetupProjection(WINDOW_WIDTH, WINDOW_HEIGHT);
  GraphicsRender->SetCameraPosition(0.0, 0.0);
}

void System::Update()
{
  stateManager->Update();
}

void System::Destroy()
{
  delete stateManager;
  delete gameObjectList;

  //Kill the window
  glfwDestroyWindow(window);

  glfwTerminate();
}