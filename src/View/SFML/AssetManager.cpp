#include "AssetManager.hpp"

#include <iostream>

using namespace View::SFML;


std::unordered_map< std::string, sf::Font * > AssetManager::fontCache;
std::unordered_map< std::string, sf::Texture * > AssetManager::textureCache;


const sf::Font * AssetManager::getFont( std::string key )
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

const sf::Texture * AssetManager::getTexture( std::string key )
{
	std::unordered_map< std::string, sf::Texture * >::const_iterator iter = AssetManager::textureCache.find( key );
	if( iter == AssetManager::textureCache.end() ) {
		std::cout << "Texture '" + key + "' not found in map. Load from file." << std::endl;
		sf::Texture * texture = new sf::Texture();
		texture->loadFromFile( "../assets/images/" + key );
        texture->setRepeated( true );
        texture->setSmooth( true );
		std::cout << texture << std::endl;
		std::pair< std::string, sf::Texture * > newFont ( key, texture );
		AssetManager::textureCache.insert( newFont );
		return texture;
	}

	return iter->second;
}
