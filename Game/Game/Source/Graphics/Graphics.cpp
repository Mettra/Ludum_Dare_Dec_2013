#include "Graphics/Graphics.h"

extern Graphics* g_glRender;
//Link in the libraries
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
void SetupPixelFormat(HDC hDC)
{
  int pixelFormat;

  PIXELFORMATDESCRIPTOR pfd =
  {   
    sizeof(PIXELFORMATDESCRIPTOR),  // size
    1,                          // version
    PFD_SUPPORT_OPENGL |        // OpenGL window
    PFD_DRAW_TO_WINDOW |        // render to window
    PFD_DOUBLEBUFFER,           // support double-buffering
    PFD_TYPE_RGBA,              // color type
    32,                         // prefered color depth
    0, 0, 0, 0, 0, 0,           // color bits (ignored)
    0,                          // no alpha buffer
    0,                          // alpha bits (ignored)
    0,                          // no accumulation buffer
    0, 0, 0, 0,                 // accum bits (ignored)
    16,                         // depth buffer
    0,                          // no stencil buffer
    0,                          // no auxiliary buffers
    PFD_MAIN_PLANE,             // main layer
    0,                          // reserved
    0, 0, 0,                    // no layer, visible, damage masks
  };

  pixelFormat = ChoosePixelFormat(hDC, &pfd);
  SetPixelFormat(hDC, pixelFormat, &pfd);
}

LRESULT CALLBACK MainWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  static HDC hDC;
  static HGLRC hRC;
  int height, width;

  // dispatch messages
  switch (uMsg)
  {   
  case WM_CREATE:         // window creation
    hDC = GetDC(hWnd);
    SetupPixelFormat(hDC);
    //SetupPalette();
    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);
    break;

  case WM_DESTROY:            // window destroy
  case WM_QUIT:
  case WM_CLOSE:                  // windows is closing

    // deselect rendering context and delete it
    wglMakeCurrent(hDC, NULL);
    wglDeleteContext(hRC);

    // send WM_QUIT to message queue
    PostQuitMessage(0);
    break;

  case WM_SIZE:
    height = HIWORD(lParam);        // retrieve width and height
    width = LOWORD(lParam);

    g_glRender->SetupProjection(width, height);

    break;

  case WM_ACTIVATEAPP:        // activate app
    break;

  case WM_PAINT:              // paint
    PAINTSTRUCT ps;
    BeginPaint(hWnd, &ps);
    EndPaint(hWnd, &ps);
    break;

  case WM_LBUTTONDOWN:        // left mouse button
    break;

  case WM_RBUTTONDOWN:        // right mouse button
    break;

  case WM_MOUSEMOVE:          // mouse movement
    break;

  case WM_LBUTTONUP:          // left button release
    break;

  case WM_RBUTTONUP:          // right button release
    break;

  case WM_KEYUP:
    break;

  case WM_KEYDOWN:
    int fwKeys;
    LPARAM keyData;
    fwKeys = (int)wParam;    // virtual-key code 
    keyData = lParam;          // key data 

    switch(fwKeys)
    {
    case VK_ESCAPE:
      PostQuitMessage(0);
      break;
    default:
      break;
    }

    break;

  default:
    break;
  }
  return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Graphics::Graphics() {
  glClearColor(0.0, 0.0, 0.0, 0.0);
}

Graphics::~Graphics() {

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
  return;
}

void Graphics::Render() {
  glEnd();
  glBegin(GL_TRIANGLES);
}

