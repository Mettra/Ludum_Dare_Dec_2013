#include <InputManager/InputManager.h>

double InputManager::mouseX;
double InputManager::mouseY;
bool   InputManager::keys[400];

void InputManager::Init() {
  glfwSetKeyCallback(System::window, &InputManager::HandleKeyboard);
  glfwSetMouseButtonCallback(System::window, &InputManager::HandleMouse);

  glfwSetCursorPosCallback(System::window, &InputManager::HandleMouseMove);
}

void InputManager::Update(){
  if (keys[GLFW_KEY_ESCAPE])
    glfwSetWindowShouldClose(System::window, true);
}

void InputManager::HandleKeyboard( GLFWwindow* window, int key, int scancode, int action, int mods ) {
  keys[key] = static_cast<bool>(action);
}

void InputManager::HandleMouse( GLFWwindow* window, int key, int action, int mods ) {
  glfwGetCursorPos(System::window, &mouseX, &mouseY);
  keys[key] = static_cast<bool>(action);
}

void InputManager::HandleMouseMove( GLFWwindow* window, double x, double y) {
  mouseX = x;
  mouseY = y;
}

bool InputManager::IsMouseClicked() {
  return keys[GLFW_MOUSE_BUTTON_LEFT];
}

bool InputManager::IsMouseClickedRight() {
  return keys[GLFW_MOUSE_BUTTON_RIGHT];
}




