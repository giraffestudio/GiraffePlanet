#include "Enemy.h"

void Enemy::update(float dt)
{
	//float moveY = dt * velocity;
	//setPosition(x, y - moveY);

	boundingBox.left = x - Width/2.0f;
	boundingBox.top = y - Height/2.0f;
}
