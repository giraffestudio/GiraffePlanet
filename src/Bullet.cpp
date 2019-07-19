#include "Bullet.h"

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
}

void Bullet::update(float dt)
{
	float moveY = dt * velocity;
	setPosition(x, y - moveY);
	
	boundingBox.left = x - 4.5f;
	boundingBox.top = y;
}
