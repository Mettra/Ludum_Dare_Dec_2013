#include "Lua.h"

lua_State *Lua = 0;

void Lua_Init()
{
  if(Lua == 0)
  { 
    Lua = luaL_newstate();
    luaL_openlibs(Lua);
  }
}

int Lua_Error (lua_State* Lua)
{
	printf("Lua Error: %s\n",lua_tostring(Lua, lua_gettop(Lua) ) );
  return -1;
}

void Lua_Destroy()
{
  lua_gc(Lua, LUA_GCCOLLECT, 0);
  lua_close(Lua);
}