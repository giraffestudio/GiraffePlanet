#include "Game.h"
#include <algorithm>
#include <random>
#include "imgui-SFML.h"

Game::~Game()
{
	ImGui::SFML::Shutdown();
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

	ImGui::SFML::Init( window );

	player.init( &resources );
	gamestate = new GameState( &player, &window, &resources );
	gamestate->LoadLevel1();
}

void Game::Run()
{
	ImGuiWindowFlags window_flags = 0 | ImGuiWindowFlags_NoMove;
	
	FrameClock.restart();
	while (window.isOpen())
	{
		frameRenderTime = FrameClock.restart();
		gamestate->handleInput();
		gamestate->update(frameRenderTime.asSeconds());
		window.resetGLStates();
		gamestate->draw();
		
		window.pollEvent( event );
		ImGui::SFML::ProcessEvent( event );
		
		ImGui::SFML::Update( window, frameRenderTime );
		
		ImGui::Begin( "Hello, world!", nullptr, window_flags );
		ImGui::Button( "Look at this pretty button" );
		ImGui::ShowDemoWindow();
		

		ImGui::End();
		ImGui::SFML::Render();
		window.display();
	}
}