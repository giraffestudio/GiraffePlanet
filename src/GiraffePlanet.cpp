#include <iostream>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
		
	game.Init();
	game.Run();
	
	return 420;
}