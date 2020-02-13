#include "Animation.h"

void Animation::AddRelativeMovement( sf::Vector2f movement )
{
	relative_movement = movement;

}

void Animation::update( const float dt )
{
	sf::Vector2f scale_props = { 0.f, 0.f };
	sf::Vector2f move_props = Sprite->getPosition();
	
	timer += dt;

	switch ( Type )
	{
		case AnimationType::SCALE : 
				if ( timer >= duration )
				{
					Sprite->setScale( dest_scale );
					break;
				}
			
				scale_props.x = begin_scale.x + ( ( dest_scale.x - begin_scale.x ) / duration ) * timer;
				scale_props.y = begin_scale.y + ( ( dest_scale.y - begin_scale.y ) / duration ) * timer;
				Sprite->setScale( scale_props );
			break;

		case AnimationType::MOVE :
			if ( timer < duration )
			{
				move_props.x += ( relative_movement.x / duration ) * dt;
				move_props.y += ( relative_movement.y / duration ) * dt;
				Sprite->setPosition( move_props );
			}
			break;
		
		case AnimationType::ROTATE:
			if ( timer < duration )
			{
				float current_rotation = Sprite->getRotation();
				Sprite->setRotation( current_rotation + ( dest_rotation * dt ) );
			}
			break;

	}
}
