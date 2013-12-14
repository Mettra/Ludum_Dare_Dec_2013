#include "Graphics/Graphics.h"
#include <System/System.h>


//Link in the libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "soil.lib")


#include <stdio.h>
//GLFW Stuff
void ErrorCallBackForGLFW(int error, const char* description  ){
  fprintf(stderr,"GLFW Err #%i: '&s'\n", error, description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
  glViewport(0, 0, width, height);
}

//GraphicsHandler
Graphics::Graphics() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_TEXTURE_2D);
  
  glGenTextures(MAX_TEXTURES, Texture);
  
}

Graphics::~Graphics() {
  glDeleteTextures(MAX_TEXTURES, Texture);
}

void Graphics::SetupProjection( int width, int height ) {
  if (height == 0)
    height = 1;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //Aspect Ratio Calculation
  gluPerspective(52.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  window_width  = width;
  window_height = height;
}

void Graphics::Init() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  return;
}

void Graphics::BeginRender(){
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glTranslatef(cameraX, cameraY, -600.0f);//1 to 1 pixel raio apparently.

  glPolygonMode(GL_FRONT, GL_FILL);
  glEnable(GL_CULL_FACE);


}

void Graphics::EndRender(){
  glfwSwapBuffers(System::window);
}

void Graphics::SetColor( unsigned char r, unsigned char g, unsigned char b, unsigned char a ) {
   glColor4ub(r, g, b, a);
}

void Graphics::DrawRect( float x, float y, float height, float width ) {
  float x1, x2, y1, y2;

  if (height < 0) height = 0.0f;
  if (width  < 0) width  = 0.0f;

  x1 = x - (width/2);
  x2 = x + (width/2);
  y1 = y + (height/2);
  y2 = y - (height/2);

  glBegin(GL_TRIANGLES);
  glVertex3f(x1,y1, 0.0f);
  glVertex3f(x1,y2, 0.0f);
  glVertex3f(x2,y2, 0.0f);

  glVertex3f(x2,y2, 0.0f);
  glVertex3f(x2,y1, 0.0f);
  glVertex3f(x1,y1, 0.0f);
  glEnd();
}

void Graphics::SetCameraPosition( float x, float y ) {
  cameraX = -x;
  cameraY = -y;
}

void Graphics::AddTexture( const char *filename, unsigned int index ) {
  Texture[index] = SOIL_load_OGL_texture(
                          filename,
                          SOIL_LOAD_AUTO,
                          SOIL_CREATE_NEW_ID,
                          SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
                          );
  glBindTexture(GL_TEXTURE_2D, Texture[index]);
  
  fprintf(stderr,"SOIL loading error: '%s'\n", SOIL_last_result() );
  
}

void Graphics::SetTexture( unsigned int id ) {
  glBindTexture(GL_TEXTURE_2D, Texture[id]);
}

void Graphics::DrawTexturedRect( float x, float y, float height, float width ) {
  float x1, x2, y1, y2;

  if (height < 0) height = 0.0f;
  if (width  < 0) width  = 0.0f;

  x1 = x - (width/2);
  x2 = x + (width/2);
  y1 = y + (height/2);
  y2 = y - (height/2);
  

  glEnable(GL_TEXTURE_2D);
  glBegin(GL_TRIANGLES);

  SetColor(255, 255, 255, 255);
  glTexCoord2f(0.0, 1.0);glVertex3f(x1,y1, 0.0f);
  glTexCoord2f(0.0, 0.0);glVertex3f(x1,y2, 0.0f);
  glTexCoord2f(1.0, 0.0);glVertex3f(x2,y2, 0.0f);

  glTexCoord2f(1.0, 0.0);glVertex3f(x2,y2, 0.0f);
  glTexCoord2f(1.0, 1.0);glVertex3f(x2,y1, 0.0f);
  glTexCoord2f(0.0, 1.0);glVertex3f(x1,y1, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}


