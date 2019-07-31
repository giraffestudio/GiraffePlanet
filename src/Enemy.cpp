#include "Enemy.h"

Enemy::Enemy(float x_pos, float y_pos, sf::Texture& spriteSheet)
{
	x = x_pos;
	y = y_pos;
	Sprite = sf::Sprite(spriteSheet, ssRect_green);
	Sprite.setPosition(x, y);
	Sprite.setOrigin(46.5, 42);
}

void Enemy::update(float dt)
{
	//float moveY = dt * velocity;
	//setPosition(x, y - moveY);

	boundingBox.left = x - Width/2.0f;
	boundingBox.top = y - Height/2.0f;
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(Sprite);
}