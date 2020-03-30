#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class ResourceMan
{
private:	
	sf::Texture spriteSheet;
	std::vector<sf::Uint8> TextureBitmask;
	std::map<std::string, sf::IntRect> spriteRects;
	std::map<std::string, sf::SoundBuffer> SoundS;
	std::map < std::string, sf::Texture > Backgrounds;
	std::map <std::string, sf::Font> Fonts;
	void LoadSpriteSheetXML(std::string fileName);

public:
	sf::IntRect getSpriteRect(std::string name);
	void playSample( std::string name );
	sf::Texture& getSpriteSheet() { return spriteSheet; }
	sf::Texture& getBackground( std::string name );
	sf::Font& getFont( std::string name );
	void LoadResources();
	std::vector<sf::Uint8> createBitmask(sf::Image& tex);
	std::vector<sf::Uint8>& getBitmask() { return TextureBitmask; };
	// some shitty stuff to get rid of
	sf::Sound sound;
};

