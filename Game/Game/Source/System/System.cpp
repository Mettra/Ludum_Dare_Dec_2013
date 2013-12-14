#include "System.h"
#include <Lua\Lua.h>
#include <string>
#include <StateManager\StateManager.h>

bool System::isActive = true;
GLFWwindow* System::window = 0;

static StateManager *stateManager = 0;


void System::Initialize()
{
  stateManager = new StateManager();
  stateManager->Initialize();
  if (!glfwInit())
    return ;

  window = glfwCreateWindow(800, 600, "A GLFW Example", NULL, NULL);
  if (!window)
  {
    glfwTerminate();
    return ;
  }
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);

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

  //Kill the window
  glfwDestroyWindow(window);

  glfwTerminate();
}