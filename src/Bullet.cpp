#include "Bullet.h"

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(Sprite, states);
}

Bullet::Bullet(float x_pos, float y_pos, float _velocity, sf::Texture* spriteSheet, Type bulletType)
{
	if(bulletType==Type::PLAYER_BULLET)	Sprite = sf::Sprite(*spriteSheet, { 856,57,9,37 });
	if(bulletType==Type::ENEMY_BULLET) Sprite = sf::Sprite(*spriteSheet, { 854,639,9,37 });
	
	Sprite.setOrigin(9.0 / 2.0f, 37.0f / 2.0f);

	setPosition(x_pos, y_pos);
	velocity = _velocity;
}

void Bullet::setPosition(float newx, float newy)
{
	x = newx;
	y = newy;

	if (x > 1919 - 56)
	{
		x = 1919 - 56;
	}
	if (x < 56)
	{
		x = 56;
	}

	Sprite.setPosition(x, y);
}

void Bullet::update(float dt)
{
	float moveY = dt * velocity;
	setPosition(x, y - moveY);
	
	boundingBox.left = x - 4.5f;
	boundingBox.top = y;
}
