#include "System/System.h"
#include "System/Meta.h"

struct S : public MetaInterface<S>
{
  int thing;
  int thing2;
  std::string info;
};

META_DEFINE(S)
{
  ADD_MEMBER(thing);
  ADD_MEMBER(thing2);
  ADD_MEMBER(info);
}

int main(void)
{
  S s;
  s.thing = 1;
  s.thing2 = 2;
  s.info = "Hi!";

  s.AddMember("dThing",new double());
  s.GetMember<double>("dThing") = 5.0;

  std::string thing = s.GetMember<std::string>("info");

  printf("%s %i %f \n",thing.c_str(),s.GetMember<int>("thing"),s.GetMember<double>("dThing"));

  //System::Initialize();
  //System::Update();

  return 0;
=======

#include "Graphics/Graphics.h"
Graphics* g_glRender = new Graphics;
int isFullscreen;
bool exiting = false;
HDC hDC; //Window device context.

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
  WNDCLASSEX windowClass;
  HWND hwnd;
  MSG msg;
  DWORD dwExStyle;
  DWORD dwStyle;
  RECT windowRect;

  g_glRender = new Graphics();

  windowRect.left   = (long)0;
  windowRect.right  = (long)WINDOW_WIDTH;
  windowRect.top    = (long)0;
  windowRect.bottom = (long)WINDOW_HEIGHT;

  windowClass.cbSize = sizeof(WNDCLASSEX);
  windowClass.style  = CS_HREDRAW | CS_VREDRAW;
  windowClass.lpfnWndProc = MainWindowProc;
  windowClass.cbClsExtra = 0;
  windowClass.cbWndExtra = 0;
  windowClass.hInstance = hInstance;
  windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
  windowClass.hbrBackground = NULL;
  windowClass.lpszMenuName = NULL;
  windowClass.lpszClassName = "GLClass";
  windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

  //Register the WindowClass
  if(!RegisterClassEx(&windowClass))
    return 0;

  if(isFullscreen){
    DEVMODE dmScreenSettings;
    memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
    dmScreenSettings.dmSize = sizeof(dmScreenSettings);
    dmScreenSettings.dmPelsWidth = WINDOW_WIDTH;
    dmScreenSettings.dmPelsHeight = WINDOW_HEIGHT;
    dmScreenSettings.dmBitsPerPel = 32;
    dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    if(ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL){
      MessageBox(NULL, "Display Mode FAILED!", NULL, MB_OK);
      isFullscreen = FALSE;
    }

  }

  if(isFullscreen){
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle   = WS_POPUP;
    ShowCursor(FALSE);
  }
  else{
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle   = WS_OVERLAPPEDWINDOW;
  }

  //Adjust to requested size
  AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

  //Create the window
  hwnd = CreateWindowEx(
    NULL,
    "GLClass",
    "GraphicsTest",
    dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
    0, 0,
    windowRect.right  - windowRect.left,
    windowRect.bottom - windowRect.top,
    NULL,
    NULL,
    hInstance,
    NULL);
  hDC = GetDC(hwnd);

  if(!hwnd)
    return 0;

  ShowWindow(hwnd, SW_SHOW);
  UpdateWindow(hwnd);

  g_glRender->Init();

  while(!exiting){

    g_glRender->SetCameraPosition(0.0, 0.0);

    g_glRender->BeginRender();

    g_glRender->SetCameraPosition(0.0, 0.0);

    g_glRender->SetColor(255, 0, 0, 255);
    g_glRender->DrawRect(0.0, 0.0, 10.0, 10.0);
    
    g_glRender->SetColor(0, 255, 0, 255);
    g_glRender->DrawRect(10.0, 0.0, 10.0, 10.0);

    g_glRender->EndRender();

    SwapBuffers(hDC);

    while(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)){
      if(!GetMessage(&msg, NULL, 0, 0)) {
        exiting = true;
        break;
      }
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  delete g_glRender;

  if(isFullscreen)
  {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(TRUE);
  }

  return (int)msg.wParam;

>>>>>>> fe11a7e31f5978f8afe43a56271c15f96dfbc504
}