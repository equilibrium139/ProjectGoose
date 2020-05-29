#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>

class ResourceHolder
{
public:
	ResourceHolder() = delete;
	static sf::Texture& GetTexture(const std::string& path);
};