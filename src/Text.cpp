#include "Text.h"

Text::Text( sf::Font& pfont, unsigned int size, std::string str, size_t position_flags, sf::Vector2f xy )
{
	text.setFont( pfont );
	text.setString( str );
	text.setFillColor( sf::Color::White );
	text.setCharacterSize( size );
	text.setStyle( sf::Text::Regular );
	
	sf::FloatRect bounds = text.getGlobalBounds();
	text.setPosition( -bounds.left, -bounds.top );

	texture = new sf::RenderTexture;
	texture->create( static_cast<int>(bounds.width), static_cast<int>(bounds.height) );
	texture->clear( sf::Color::Transparent );
	texture->draw( text );
	texture->setSmooth( true );
	texture->display();
	sprite.setTexture( texture->getTexture() );
	
	if ( position_flags & static_cast<size_t>(Alignement::HORIZONTAL_CENTER ) ) 
	{
		xy.x = ( 1920.f - bounds.width ) / 2.f;
	}
	
	if ( position_flags & static_cast<size_t>( Alignement::VERTICAL_CENTER ) ) 
	{		
		xy.y = ( 1080.f - bounds.height ) / 2.f;		
	}
	sprite.setPosition( xy );
}

void Text::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( sprite, states );
}


