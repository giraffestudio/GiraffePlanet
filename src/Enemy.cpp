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
	boundingBox.left = x - Width/2.0f;
	boundingBox.top = y - Height/2.0f;

	// delete animation that are finished
	auto isAnimationFinished = []( Animation testedAnimation ) { return testedAnimation.isFinshed(); };
	animations.erase( std::remove_if( animations.begin(), animations.end(), isAnimationFinished ), animations.end() );

	for ( auto & animations : animations ) {
		animations.update( dt );
	}

	debris.update( dt );
}

void Enemy::fire()
{

}

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// draw enemy
	target.draw( debris );
	target.draw(Sprite, states);
}

void Enemy::hit()
{
	rotation += 25 - rand() % 50;
	Animation HitAnimation(&Sprite, true);
	HitAnimation.AddMovement( { 0,-20 }, 0.6f );
	animations.push_back( HitAnimation );
	
	HitAnimation.AddRotation( rotation, 0.6f );
	animations.push_back( HitAnimation );
		
	debris.setEmitterPosition( { x,y } );
	debris.setEmitterWidth( 1.f );
	debris.setEmitterSpawnRate( 0.0005f );
	debris.setSpeed( 455.f, 685.f );
	debris.setColor( { static_cast<sf::Uint8>(rand()%250),215,60,255 } );
	debris.setParticleLifetime( 0.8f );
	
	debris.enable( 0.10f );

	HP--;
}

void Enemy::enable()
{
	enabled = true;
	for ( auto& animation : animations ) animation.enable();
}

void Enemy::disable()
{
	enabled = false;
	for ( auto& animation : animations ) animation.disable();
}
