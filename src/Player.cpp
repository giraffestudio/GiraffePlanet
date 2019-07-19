#include "Player.h"

Player::Player()
{
	Texture.loadFromFile("../res/PNG/playerShip2_orange.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(56, 75 / 2);
	Sprite.setPosition(x, y);

	
	DamageTextures.reserve(3);
	DamageTextures[0].loadFromFile("../res/PNG/Damage/playerShip2_damage1.png" ) ;
	DamageTextures[1].loadFromFile("../res/PNG/Damage/playerShip2_damage2.png" ) ;
	DamageTextures[2].loadFromFile("../res/PNG/Damage/playerShip2_damage3.png") ;
}

void Player::update(float dt)
{
	double moveY = dt * velocityY;
	double moveX = dt * velocityX;

	setPosition(x+moveX,  y+moveY);

	boundingBox.left = x - 56;
	boundingBox.top = y-75.0f/2.f;

}


void Player::setPosition(double newx, double newy)
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
	
	if ( (newy > Height/ 2+10 ) && (newy < 1080-Height/2-10) ) y = newy;
	
	Sprite.setPosition(x, y);
}
