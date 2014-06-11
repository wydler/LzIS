#include "AssetManager.hpp"

#include <iostream>

using namespace View;


std::unordered_map< std::string, sf::Font * > AssetManager::fontCache;

sf::Font * AssetManager::getFont( std::string key )
{
	std::unordered_map< std::string, sf::Font * >::const_iterator iter = AssetManager::fontCache.find( key );
	if( iter == AssetManager::fontCache.end() ) {
		std::cout << "Font '" + key + "' not found in map. Load from file." << std::endl;
		sf::Font * font = new sf::Font();
		font->loadFromFile( "../assets/fonts/" + key );
		std::cout << font << std::endl;
		std::pair< std::string, sf::Font * > newFont ( key, font );
		AssetManager::fontCache.insert( newFont );
		return font;
	}

	return iter->second;
}