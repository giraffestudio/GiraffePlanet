#include "ResourceMan.h"

void ResourceMan::LoadResources()
{
	sf::Image SpriteSheetImage;
	SpriteSheetImage.loadFromFile( "../RES/SpriteSheet/sheet_cor.png" );
	TextureBitmask = createBitmask( SpriteSheetImage );

	spriteSheet.loadFromImage( SpriteSheetImage );
	spriteSheet.setSmooth( true );
	LoadSpriteSheetXML("../res/Spritesheet/sheet.xml");

	// Loading of sounds
	//* Game Over
	sf::SoundBuffer sound;
	sound.loadFromFile( "../res/Sound/Laser_1.wav" );
	SoundS.insert( std::make_pair( "Laser_1", sound ) );
	
	sound.loadFromFile( "../res/Sound/GameOver_1.wav" );
	SoundS.insert( std::make_pair( "GameOver_1", sound ) );

	//load backgrounds
	sf::Texture tex;
	tex.loadFromFile( "../res/Backgrounds/purple.png" );
	tex.setRepeated( true );
	Backgrounds.insert( std::make_pair( "Purplee",tex ));
	tex.loadFromFile( "../res/Backgrounds/black.png" );
	tex.setRepeated( true );
	Backgrounds.insert( std::make_pair( "Black", tex ) );

	// load fonts
	sf::Font font;
	font.loadFromFile( "../res/fonts/atari.ttf" );
	Fonts.insert( std::make_pair( "Atari", font ) );
	font.loadFromFile( "../res/fonts/arial.ttf" );
	Fonts.insert( std::make_pair( "Arial", font ) );
	font.loadFromFile( "../res/fonts/HNPro.ttf" );
	Fonts.insert( std::make_pair( "HNPro", font ) );
	font.loadFromFile( "../res/fonts/HelveticaNeueLTPro-LtCn.ttf" );
	Fonts.insert( std::make_pair( "HelveticaNeueLTPro-LtCn", font ) );
}

std::vector<sf::Uint8> ResourceMan::createBitmask( sf::Image& img )
{
	std::vector<sf::Uint8> bitmask( static_cast<size_t>(img.getSize().x) * static_cast<size_t>(img.getSize().y) );
	
	for ( size_t y = 0; y < img.getSize().y; ++y )
		for ( size_t x = 0; x < img.getSize().x; ++x )
			bitmask[y * img.getSize().y + x] = img.getPixel( static_cast<unsigned int>(x), static_cast<unsigned int>(y) ).a;
	return bitmask;
}

void ResourceMan::LoadSpriteSheetXML(std::string fileName)
{
	std::vector<char> spriteSheetXML;

	spriteRects.clear();
	std::ifstream file;
	file.open(fileName);
	file.unsetf(std::ios::skipws);

	// Determine stream size
	file.seekg(0, std::ios::end);
	size_t size = file.tellg();
	file.seekg(0);

	// Load data and add terminating 0
	spriteSheetXML.resize(size + 1);
	file.read(&spriteSheetXML.front(), static_cast<std::streamsize>(size));
	spriteSheetXML[size] = 0;

	rapidxml::xml_document<char>* doc = new rapidxml::xml_document<char>;
	doc->parse<0>(spriteSheetXML.data());
	rapidxml::xml_node<>* top_node = doc->first_node();

	for (rapidxml::xml_node<>* node = top_node->first_node(); node; node = node->next_sibling())
	{
		sf::IntRect spriteRect;
		std::string spriteName;
		spriteName		= node->first_attribute("name")->value();
		spriteRect.left = std::stoi(node->first_attribute("x")->value());
		spriteRect.top = std::stoi(node->first_attribute("y")->value());
		spriteRect.width = std::stoi(node->first_attribute("width")->value());
		spriteRect.height = std::stoi(node->first_attribute("height")->value());

		spriteRects.insert(std::make_pair(spriteName, spriteRect));
	}

	delete doc;
	spriteSheetXML.clear();
}

sf::IntRect ResourceMan::getSpriteRect(std::string name)
{
	return spriteRects[name];
}

void ResourceMan::playSample( std::string name )
{
	sound.setBuffer( SoundS[name] );
	sound.play();
}
sf::Texture& ResourceMan::getBackground( std::string name )
{
	return Backgrounds[name];
}

sf::Font& ResourceMan::getFont( std::string name )
{
	return Fonts[name];
}
