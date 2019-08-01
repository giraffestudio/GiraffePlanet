#include "ResourceMan.h"

void ResourceMan::LoadSpriteSheetXML(std::string fileName)
{
	spriteRects.clear();
	spriteSheetXML.clear();

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

	rapidxml::xml_document<char> doc;
	doc.parse<0>(spriteSheetXML.data());
	rapidxml::xml_node<>* top_node = doc.first_node();

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
}

sf::IntRect ResourceMan::getSpriteRect(std::string name)
{
	return spriteRects[name];
}