#include <include\lua.hpp>
#include <vector>

extern lua_State* Lua;

void Lua_Init();
void Lua_Destroy();
int Lua_Error(lua_State* Lua);