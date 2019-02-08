#pragma once
#include "lua.hpp"
#include <iostream>

void run_lua_Function()
{
	auto NativeAdd = [](lua_State *L) -> int
	{
		auto a = lua_tonumber(L, -1); //read numbers from the stack
		auto b = lua_tonumber(L, -2);
		auto sum = (a + b); //load sum variable
		lua_pushnumber(L, sum); //push sum onto the stack
		return 1; //telling lua we pushed one result
	};

	//writing NativeAdd lets us call a native function in our C++ code
	//R -- raw string
	const char *lua_file = R"( 
         function add(a, b)
               val = NativeAdd(a, b)
               return val
         end
         )";


	lua_State *L = luaL_newstate();
	lua_pushcfunction(L, NativeAdd); //push the pointer to NativeAdd function onto the Lua stack
	lua_setglobal(L, "NativeAdd"); //set a global named NativeAdd to the C function we just pushed onto the stack


	luaL_dostring(L, lua_file);
	lua_getglobal(L, "add"); //push the function add onto the stack

	//check if the item at -1 on the stack is a lua function
	if (lua_isfunction(L, -1)) //-1 allows us to check the last thing that was pushed onto the stack
	{
		lua_pushnumber(L, 10); // push number 3 into lua function paramater a
		lua_pushnumber(L, 30); // push number 4 into lua function paramater a

		const int nmberArgs = 2;
		const int nmberReturnVals = 1;

		//if the call to the function does not return zero it is successful
		if (lua_pcall(L, nmberArgs, nmberReturnVals, 0) != 0) //pass in lua state, the number of arguments of your function, the number of return values and pass in an error handler if needed
			std::cout << "Function call error" << std::endl;

		auto sum = lua_tonumber(L, -1); //get the return value of the function from the stack
		auto a = lua_tonumber(L, -2);
		auto b = lua_tonumber(L, -3);

		std::cout << "Sum = " << (int)sum << std::endl;
		std::cout << "a: " << (int)a << std::endl;
		std::cout << "b: " << (int)b << std::endl;
	}

	lua_close(L);
}