#include <System\Level.h>

#define COLLISION_BOTTOM 0x00000001
#define COLLISION_LEFT   0x00000002
#define COLLISION_RIGHT  0x00000004
#define COLLISION_TOP    0x00000008

int DetectCollision(float x, float y,float width, float height);