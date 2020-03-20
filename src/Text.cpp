#include "Text.h"

Text::Text( sf::Font& pfont, std::string str, TextPosition pos, sf::Vector2f xy )
{
	text.setFont( pfont );
	text.setString( str );
	text.setFillColor( sf::Color::White );
	text.setCharacterSize( 100 );
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
	
	if ( pos == TextPosition::CENTERED )
	{
		float new_x = ( 1920.f - bounds.width ) / 2.f;
		float new_y = ( 1080.f - bounds.height ) / 2.f;
		sprite.setPosition( { new_x, new_y } );
	}
	else
	{
		sprite.setPosition( xy );
	}
	
}

void Text::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( sprite, states );
}


