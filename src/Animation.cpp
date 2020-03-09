#include "Animation.h"
#include <iostream>
void Animation::AddMovement( sf::Vector2f movement, float duration_sec )
{
	begin_position = Sprite->getPosition();
	end_position = begin_position + movement;
	relative_movement = movement;
	Type = AnimationType::MOVE;
	duration = duration_sec;
}

void Animation::AddRotation( const float rotation_deg, float duration_sec )
{
	current_rotation = Sprite->getRotation();
	begin_rotation = current_rotation;
	dest_rotation = rotation_deg;
	Type = AnimationType::ROTATE;
	duration = duration_sec;
}

void Animation::update( const float dt )
{
	if ( enabled == false ) return;
	sf::Vector2f scale_props = { 0.f, 0.f };
	sf::Vector2f new_position;
	
	timer += dt;
	if ( timer >= duration ) {
		finished = true;
	}

	switch ( Type )
	{
		case AnimationType::SCALE : 
			if ( timer < duration )
			{
				scale_props.x = begin_scale.x + ( ( dest_scale.x - begin_scale.x ) / duration ) * timer;
				scale_props.y = begin_scale.y + ( ( dest_scale.y - begin_scale.y ) / duration ) * timer;
				Sprite->setScale( scale_props );
			}
			else
			{
				Sprite->setScale( dest_scale );
			}
			break;

		case AnimationType::MOVE :
			if ( timer < duration )
			{
				new_position.x = begin_position.x + ( relative_movement.x * timer / duration );
				new_position.y = begin_position.y + ( relative_movement.y * timer / duration );
				Sprite->setPosition( new_position );
			}
			else
			{
				Sprite->setPosition( end_position );
			}
			break;
		
		case AnimationType::ROTATE:
			if ( timer < duration )
			{
				current_rotation = begin_rotation + ((dest_rotation-begin_rotation)/duration) * timer;
				Sprite->setRotation( current_rotation );		
			}
			else
			{
				Sprite->setRotation( dest_rotation );
			}
			break;

		case AnimationType::ALPHA:
			if( timer < duration )
			{
				float step = abs( end_alpha - begin_alpha ) / duration;
				current_alpha += step * dt;
				Sprite->setColor( sf::Color( 255, 255, 255, current_alpha ) );
			}
			else
			{
				Sprite->setColor( sf::Color( 255, 255, 255, end_alpha ) );
			}
			break;
	}
}
