#include <System/System.h>
//Casting 'int's to 'bool's
#pragma warning(disable: 4800)  

enum Actions{


};

class InputManager{
  static double mouseX;
  static double mouseY;

  static bool keys[400];

  static void HandleKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
  static void HandleMouse(GLFWwindow* window, int key, int action, int mods);
  static void HandleMouseMove(GLFWwindow* windowd, double x, double y);

public:
  InputManager();
  ~InputManager();

  static void Init();
  static void Update();
  static bool IsKeyPressed(int key){return keys[key];};
  static bool IsKeyTriggered(int key){return keys[key];};
  static float GetMouseX();
  static float GetMouseY();
  
  static bool IsMouseClicked();
  static bool IsMouseClickedRight();
  
  static bool AnyKeyInput();

  
  

};