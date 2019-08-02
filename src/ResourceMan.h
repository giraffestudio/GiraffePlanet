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
	std::map<std::string, sf::IntRect> spriteRects;
	
	void LoadSpriteSheetXML(std::string fileName);

public:
	sf::IntRect getSpriteRect(std::string name);
	sf::Texture& getSpriteSheet() { return spriteSheet; }
	void LoadResources();

	// some shitty stuff to get rid of
	sf::SoundBuffer sbGameOver;
	sf::SoundBuffer sbPlayerFire;
	sf::Sound sound;
};

