#include <stdio.h>
#include <lua.h> // 这里的函数都 lua_开头
#include <lauxlib.h> // 这是一个辅助库 这里面的函数都是luaL_开头
#include <lualib.h> // 读写函数等，全都放在这里

int main(void)
{
	char buff[256];
	int error;
	lua_State *L = lua_open(); // 打开Lua

							   // 打开各种库
	luaopen_base(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);
	luaopen_math(L);

	while (fgets(buff, sizeof(buff), stdin) != NULL)
	{
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") // 读取用户输入，并且压入栈。没有错误的情况下，返回0
			|| lua_pcall(L, 0, 0, 0);//lua_pcall -> 调用Lua的函数，将chunk从栈中弹出，并且在保护模式下运行，这里就是“闭包函数”。没有错误的情况下，返回0


									 // 如果有错误，这两个函数luaL_loadbuffer和lua_pcall将一条错误消息压入栈中，
		if (error)
		{
			fprintf(stderr, "%s", lua_tostring(L, -1));// lua_tostring得到上面的错误信息
			lua_pop(L, 1);// lua_pop将上面的错误信息从栈中删除
		}
	}

	lua_close(L);
	return 0;
}