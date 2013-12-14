#ifndef GRAPHICS_H
#define GRAPHICS_H

#define GLFW_INCLUDE_GLU
#include "GLFW/glfw3.h"

//Image Handling
#include <include/SOIL.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAX_TEXTURES 64

//GLFW Stuff
void ErrorCallBackForGLFW(int error, const char* description  );
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

class Graphics {
  unsigned int window_width;
  unsigned int window_height;

  float cameraX;
  float cameraY;

  GLuint Texture[MAX_TEXTURES];

public:
  Graphics();
  ~Graphics();

  void Init();

  void SetupProjection( int width, int height );

  void SetCameraPosition(float x, float y);

  void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  void DrawRect(float x, float y, float height, float width);

  void BeginRender();
  void EndRender();


  void AddTexture(const char *filename, unsigned int index);

  void SetTexture(unsigned int id);
  void DrawTexturedRect(float x, float y, float height, float widt);

};



extern Graphics* GraphicsRender;


#endif