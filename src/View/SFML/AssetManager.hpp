#ifndef _VIEW_SFML_ASSETMANAGER_INCLUDED_
#define _VIEW_SFML_ASSETMANAGER_INCLUDED_


#include <SFML/Graphics.hpp>

#include <unordered_map>


namespace View
{
    namespace SFML
    {
        class AssetManager
        {
        public:
            static const sf::Font * getFont( std::string );
            static const sf::Texture * getTexture( std::string );
        private:
            static std::unordered_map< std::string, sf::Font * > fontCache;
            static std::unordered_map< std::string, sf::Texture * > textureCache;
        };
    }
}


#endif
