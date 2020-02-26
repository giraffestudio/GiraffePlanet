#include "Game.h"
#include <algorithm>
#include <random>

Game::~Game()
{
	delete gamestate;
}

void Game::Init()
{
	resources.LoadResources();

	// When in debug mode do not use full screen - it sucks to switch back to IDE through task manager
#ifdef _DEBUG
	sf::VideoMode FullScreen = sf::VideoMode( 1920, 1080, 32 );
	sf::Uint32 WindowStyle = sf::Style::Resize;
#else
	sf::VideoMode FullScreen = sf::VideoMode( 1920, 1080, 32 );
	sf::Uint32 WindowStyle = sf::Style::Fullscreen;
#endif // _DEBUG

	Settings.antialiasingLevel = 8;
	
	window.create( FullScreen, "Game", WindowStyle, Settings );
	window.setFramerateLimit( 75 );
	window.setVerticalSyncEnabled( true );
	window.setMouseCursorVisible( false );

	player.init( &resources );
	gamestate = new GameState( &player, &window, &resources );
	gamestate->LoadLevel1();
}

void Game::Run()
{
	while (window.isOpen())
	{
		frameRenderTime = FrameClock.restart();
		gamestate->handleInput();
		gamestate->update(frameRenderTime.asSeconds());
		gamestate->draw();
	}
}