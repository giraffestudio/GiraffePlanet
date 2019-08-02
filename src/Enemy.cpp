#include "Enemy.h"

Enemy::Enemy(float x_pos, float y_pos, ResourceMan* pResources)
{
	x = x_pos;
	y = y_pos;

	resources = pResources;

	Sprite = sf::Sprite(resources->getSpriteSheet(), resources->getSpriteRect("enemyGreen1.png"));
	Sprite.setPosition(x, y);
	Sprite.setOrigin(46.5, 42);
}

void Enemy::update(float dt)
{
	//float moveY = dt * velocity;
	//setPosition(x, y - moveY);

	boundingBox.left = x - Width/2.0f;
	boundingBox.top = y - Height/2.0f;

	// say goodbye to bullets that fly off screen
	auto isBulletOffScreen = [](Bullet testedBullet) { return ((testedBullet.y < 0) || (testedBullet.y > 1080)); };
	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), isBulletOffScreen), bullets.end());

	// update bullets that still enjoy flying through space
	for (auto& bullet : bullets)
	{
		bullet.update(dt);
	}
}

void Enemy::fire()
{
	bullets.emplace_back(x, y, -700.0f, resources, Bullet::Type::ENEMY_BULLET);
}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// draw enemy
	target.draw(Sprite, states);
	
	// and his stinking bullets
	for (auto& bullet : bullets)
	{
		target.draw(bullet, states);
	}

}