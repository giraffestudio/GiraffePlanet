#include "MeinMenu.h"

void MeinMenu::update( const float dt )
{


}
void MeinMenu::handleInput()
{
	sf::Event event;
	while ( window->pollEvent( event ) )
	{
		if ( event.type == sf::Event::KeyPressed )
		{
			if ( event.key.code == sf::Keyboard::Escape ) window->close();
		}
		if ( event.type == sf::Event::Closed ) window->close();
	}

	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Space ) ) player->fire();
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) player->velocityX = player->maxSpeed;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) player->velocityX = -player->maxSpeed;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) player->velocityY = player->maxSpeed;
	if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) player->velocityY = -player->maxSpeed;
	if ( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) == false ) && ( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) == false ) ) player->velocityX = 0;
	if ( ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) == false ) && ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) == false ) ) player->velocityY = 0;

}
void MeinMenu::draw()
{
	//window->draw( Background );



	window->display();
}