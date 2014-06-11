#ifndef _VIEW_ASSETMANAGER_INCLUDED_
#define _VIEW_ASSETMANAGER_INCLUDED_


#include <SFML/Graphics.hpp>

#include <unordered_map>


namespace View
{
    class AssetManager
    {
    public:
        static sf::Font * getFont( std::string );
    private:
        static std::unordered_map< std::string, sf::Font * > fontCache;
    };
}


#endif
