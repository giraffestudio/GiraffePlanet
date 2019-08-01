#pragma once


#include <SFML/Graphics.hpp>
#include "rapidxml.hpp"
#include <fstream>
#include <iostream>
#include <map>
#include <string>

class ResourceMan
{
private:	
	std::map<std::string, sf::IntRect> spriteRects;
	std::vector<char> spriteSheetXML;

public:
	void LoadSpriteSheetXML(std::string fileName);
	sf::IntRect getSpriteRect(std::string name);
};

