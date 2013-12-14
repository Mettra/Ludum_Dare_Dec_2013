#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#include <windows.h>

#include <gl/GL.h>
#include <gl/GLU.h>


void SetupPixelFormat(HDC hDC);
LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


class Graphics {
  unsigned int window_width;
  unsigned int window_height;

public:
  Graphics();
  ~Graphics();

  void Init();

  void SetupProjection( int width, int height );

  void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
  void DrawRect(int x, int y, unsigned height, unsigned width);

  
  void Render();


};

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600