#include <stdio.h>
#include <lua.h> // ����ĺ����� lua_��ͷ
#include <lauxlib.h> // ����һ�������� ������ĺ�������luaL_��ͷ
#include <lualib.h> // ��д�����ȣ�ȫ����������

int main(void)
{
	char buff[256];
	int error;
	lua_State *L = lua_open(); // ��Lua

							   // �򿪸��ֿ�
	luaopen_base(L);
	luaopen_table(L);
	luaopen_io(L);
	luaopen_string(L);
	luaopen_math(L);

	while (fgets(buff, sizeof(buff), stdin) != NULL)
	{
		error = luaL_loadbuffer(L, buff, strlen(buff), "line") // ��ȡ�û����룬����ѹ��ջ��û�д��������£�����0
			|| lua_pcall(L, 0, 0, 0);//lua_pcall -> ����Lua�ĺ�������chunk��ջ�е����������ڱ���ģʽ�����У�������ǡ��հ���������û�д��������£�����0


									 // ����д�������������luaL_loadbuffer��lua_pcall��һ��������Ϣѹ��ջ�У�
		if (error)
		{
			fprintf(stderr, "%s", lua_tostring(L, -1));// lua_tostring�õ�����Ĵ�����Ϣ
			lua_pop(L, 1);// lua_pop������Ĵ�����Ϣ��ջ��ɾ��
		}
	}

	lua_close(L);
	return 0;
}