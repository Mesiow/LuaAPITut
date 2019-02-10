#pragma once
#include "lua.hpp"
#include <iostream>

///////Example 1
//////
/////
////

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
		lua_pushnumber(L, 30); // push number 4 into lua function paramater b

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


//EXAMPLE 2
///////
//////
/////
////
void run_lua_func2()
{
	
	struct Vector2
	{
		Vector2(float x, float y)
			:x(x), y(y){}

		float x, y;
	};

	struct Sprite
	{
		Vector2 pos;
		void move(Vector2 v)
		{
			pos.x += v.x;
			pos.y += v.y;
		}
	};


	auto createSprite = [](lua_State *L) -> int
	{
		//pass in state and size in bytes of our type we want lua to use
		//lua_newuserdata returns a void pointer so we need
		//to cast it to the pointer of the type we want, it is then
		//pushed onto the lua stack
		Sprite *sprite = (Sprite*)lua_newuserdata(L, sizeof(Sprite));
		sprite->pos.x = 0;
		sprite->pos.y = 0;

		return 1; //return 1 value on the stack
	};

	auto moveSprite = [](lua_State *L)->int
	{
		Sprite *sprite = (Sprite*)lua_touserdata(L, -3);
		auto x = lua_tonumber(L, -2);
		auto y = lua_tonumber(L, -1);

		sprite->move(Vector2(x, y));
		return 0;
	};

	//lua can now create the sprite an assign it to the global sprite
	const char *script = R"(
     sprite=createSprite()
     moveSprite(sprite, 4, 2)  
    )";

	lua_State *L = luaL_newstate();

	lua_pushcfunction(L, createSprite); //push createVector function onto stack
	lua_setglobal(L, "createSprite"); //set global function name

	lua_pushcfunction(L, moveSprite); //push moveSprite function onto stack
	lua_setglobal(L, "moveSprite");

	luaL_dostring(L, script); //run script
	lua_getglobal(L, "sprite"); //get the global called sprite from the stack

	if (lua_isuserdata(L, -1)) //check if the last variable on the stack is a userdata type
	{
		std::cout << "Data obtained from Lua" << std::endl;
		Sprite *s = (Sprite*)lua_touserdata(L, -1); //since the userdata was the last thing on the stack lets grab it

		std::cout << s->pos.x << ", " << s->pos.y << std::endl;
	}
	else
		std::cout << "Data not obtained from Lua" << std::endl;

}