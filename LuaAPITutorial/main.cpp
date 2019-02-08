#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Lua_Functions.h"

int main()
{
	srand(time(NULL));
	//lua types

	//boolean
	//light userdata -- pointer type in lua (a C pointer)
	//number -- any int, double or floating point number
	//string 
	//table -- similar to an array, struct or map
	//function 
	//userdata --allows us to create our own types
	//thread

	//{

	//	/*create a new lua state(lua interpreter)*/
	//	lua_State *L = luaL_newstate(); //lua allocates memory itself and returns pointer here

	//	luaL_dostring(L, "x=22"); //execute some lua code setting the number x to 22

	//	lua_getglobal(L, "x"); //retrieve global variable x and pushes x on top of the lua stack instead of it returning a value to us

	//	//lua_Number is a typedef for a double type
	//	lua_Number x = lua_tonumber(L, 1); //1 is the position on the stack that we want to access, so we take the value at postion 1 on the lua stack
	//	std::cout << "Number: " << (int)x << std::endl;
	//	
	//	for (int i = 1; i < 5; ++i) //push 5 numbers onto the lua stack
	//	{
	//		auto number = 1 + rand() %20;
	//		lua_pushnumber(L, number);
	//	}

	//	for (int i = 1; i < 5; ++i)
	//	{
	//		auto number = lua_tonumber(L, i); //access position at the stack i and retrieve that number at the position
	//		std::cout << "Number at " << i << ": " << (int)number << std::endl;
	//	}


	//	lua_close(L); //deallocate the memory that lua allocated for us
	//}

	run_lua_Function();

	std::cin.get();
	return 0;
}