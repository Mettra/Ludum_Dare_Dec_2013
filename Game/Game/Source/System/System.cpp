#include "System.h"
#include  "Graphics/Graphics.h"


GLFWwindow* System::window;

void System::Initialize()
{
  glfwSetErrorCallback(ErrorCallBackForGLFW);

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

  while (!glfwWindowShouldClose(window))
  {
    // Keep running
    double time = glfwGetTime();
    //Begin Graphics
    GraphicsRender->BeginRender();

    

    GraphicsRender->EndRender();
    //End Graphics
    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  //Kill the window
  glfwDestroyWindow(window);



  glfwTerminate();
}