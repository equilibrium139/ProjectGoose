#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourceHolder
{
public:
	static sf::Texture& GetTexture(const std::string& path);
private:
	static std::unordered_map<std::string, sf::Texture> textures;
};