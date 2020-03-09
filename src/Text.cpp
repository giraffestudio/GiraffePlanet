#include "Text.h"

Text::Text( sf::Font& pfont, std::string str, TextPosition pos, sf::Vector2f xy )
{
	text.setFont( pfont );
	text.setString( str );
	text.setFillColor( sf::Color::White );
	text.setCharacterSize( 100 );
	text.setStyle( sf::Text::Regular );
	
	
	
	if ( pos == TextPosition::CENTERED )
	{
		sf::FloatRect bounds = text.getGlobalBounds();
		float new_x = 1920 / 2 - bounds.width / 2;
		float new_y = 1080 / 2 - bounds.height / 2;
		text.setPosition( { new_x, new_y } );
	}
	else
	{
		text.setPosition( xy );
	}
	
	
}

void Text::draw( sf::RenderTarget& target, sf::RenderStates states ) const
{
	target.draw( text, states );
}


