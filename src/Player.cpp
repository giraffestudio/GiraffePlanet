#include "Player.h"

Player::Player()
{
	Texture.loadFromFile("../res/PNG/playerShip2_orange.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(56, 0);
	Sprite.setPosition(x, y);
}
 
void Player::setPosition(float newx, float newy)
{

	if (newx > 1919 - Width / 2)
	{
		x = 1919 - Width / 2;
	}
	else
	{
		x = newx;
	}
	if (x < 56)
	{
		x = 56;
	}
	y = newy;
	Sprite.setPosition(x, y);
}
