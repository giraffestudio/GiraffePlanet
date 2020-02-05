#pragma once
#include "GameState.h"
class MeinMenu :public GameState
{
	MeinMenu( Player* pplayer, sf::RenderWindow* pwindow, ResourceMan* pResources ) : GameState( pplayer, pwindow, pResources ) {};
	virtual void draw();
	virtual void update( const float dt );
	virtual void handleInput();
};

