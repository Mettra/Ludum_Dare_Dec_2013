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
  //glEnable(GL_TEXTURE_2D);
  
  currentTime = 0.0;
  glfwSwapInterval(1);
  currentId = 0;


  glEnable(GL_ALPHA_TEST);
  glEnable( GL_BLEND );
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Graphics::~Graphics() {
}

void Graphics::SetupProjection( int width, int height ) {
  if (height == 0)
    height = 1;

  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glOrtho(-width/2, width/2, -height/2, height/2, 100.0, 1100.0);

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
  double time = glfwGetTime();
  dt = time - currentTime;
  double maxFramerate = FRAMERATE_MAX;
  
  while( dt < maxFramerate){
    time = glfwGetTime();
    dt = time - currentTime; 
  }
  currentTime = time;

  glClearColor(0.0, 0.0, 0.0, 0.0);
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

unsigned Graphics::AddTexture( const char *filename) {
  
  Texture.push_back ( SOIL_load_OGL_texture( filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT ) ) ;
  

  
  fprintf(stderr,"SOIL loading status: '%s'\n", SOIL_last_result() );
  currentId++;

  return Texture.size()-1;
}

void Graphics::FreeTexture( unsigned id ) {
  glDeleteTextures(1, &Texture.at(id));

}


void Graphics::SetTexture( unsigned int id ) {
  glBindTexture(GL_TEXTURE_2D, Texture.at(id));
  textureX1 = 0;
  textureX2 = 1;
  textureY1 = 1;
  textureY2 = 0;

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
  glEnable( GL_BLEND );
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBegin(GL_TRIANGLES);

  SetColor(255, 255, 255, 255);
  glTexCoord2f(textureX1, textureY1);glVertex3f(x1,y1, 0.0f);
  glTexCoord2f(textureX1, textureY2);glVertex3f(x1,y2, 0.0f);
  glTexCoord2f(textureX2, textureY2);glVertex3f(x2,y2, 0.0f);

  glTexCoord2f(textureX2, textureY2);glVertex3f(x2,y2, 0.0f);
  glTexCoord2f(textureX2, textureY1);glVertex3f(x2,y1, 0.0f);
  glTexCoord2f(textureX1, textureY1);glVertex3f(x1,y1, 0.0f);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}

void Graphics::TextureFlipHorizontal() {
  textureX1 = 1;
  textureX2 = 0;
}

void Graphics::TextureFlipVertical() {
  textureY1 = 0;
  textureY2 = 1;
}


