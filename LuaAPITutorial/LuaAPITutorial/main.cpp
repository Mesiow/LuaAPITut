#include <iostream>
#include "lua.hpp"

int main()
{

	//lua types

	//boolean
	//light userdata -- pointer type in lua (a C pointer)
	//number -- any int, double or floating point number
	//string 
	//table -- similar to an array, struct or map
	//function 
	//userdata --allows us to create our own types
	//thread

	{

		//create a new lua state(lua interpreter)
		lua_State *L = luaL_newstate(); //lua allocates memory itself and returns pointer here

		luaL_dostring(L, "x=22"); //execute some lua code setting the number x to 22

		lua_getglobal(L, "x"); //retrieve global variable x and pushes x on top of the lua stack instead of it returning a value to us

		//lua_Number is a typedef for a double type
		lua_Number x = lua_tonumber(L, 1); //1 is the position on the stack that we want to access, so we take the value at postion 1 on the stack
		std::cout << "Number: " << (int)x << std::endl;


		lua_close(L); //deallocate the memory that lua allocated for us
	}


	std::cin.get();
	return 0;
}