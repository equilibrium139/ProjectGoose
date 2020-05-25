#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourceHolder
{
public:
	sf::Texture& GetTexture(const std::string& path);
private:
	std::unordered_map<std::string, sf::Texture> textures;
};