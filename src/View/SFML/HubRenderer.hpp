#ifndef _VIEW_SFML_HUBRENDERER_INCLUDED_
#define _VIEW_SFML_HUBRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Station/Hub.hpp"


namespace View
{
    namespace SFML
    {
        class HubRenderer : public AUnorderedRenderer< Model::Hub >
        {
        public:
            HubRenderer( sf::RenderWindow & window ) : window(window) {}
            virtual ~HubRenderer() {}
            virtual void draw() const override;
        private:
            sf::RenderWindow & window;
        };
    }
}


#endif
