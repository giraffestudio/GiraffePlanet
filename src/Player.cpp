#include "Player.h"

Player::Player()
{
	Texture.loadFromFile("../res/PNG/playerShip2_orange.png");
	Sprite.setTexture(Texture);
	Sprite.setOrigin(56, 75 / 2);
	Sprite.setPosition(x, y);

	
	DamageTextures.emplace_back();
	DamageTextures.emplace_back();
	DamageTextures.emplace_back();

	DamageTextures[0].loadFromFile("../res/PNG/Damage/playerShip2_damage1.png" );
	DamageTextures[1].loadFromFile("../res/PNG/Damage/playerShip2_damage2.png" );
	DamageTextures[2].loadFromFile("../res/PNG/Damage/playerShip2_damage3.png");

	DamageSprites.reserve(3);
	DamageSprites.emplace_back();
	DamageSprites.emplace_back();
	DamageSprites.emplace_back();

	int i = 0;
	for (auto& ds : DamageSprites)
	{
		ds.setTexture(DamageTextures[i++]);
		ds.setOrigin(56, 75 / 2);
	}
	
}

void Player::update(float dt)
{
	float moveY = dt * velocityY;
	float moveX = dt * velocityX;

	setPosition(x+moveX,  y+moveY);

	boundingBox.left = x - 56;
	boundingBox.top = y-75.0f/2.f;

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
	
	if ( (newy > Height/ 2.0f+10.0f ) && (newy < 1080.0f-Height/2.0f-10.0f) ) y = newy;
	
	Sprite.setPosition(x, y);
	for( auto& ds : DamageSprites)
	{
		ds.setPosition(x, y);
	}
}
