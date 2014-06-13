#ifndef _VIEW_SFML_HUBRENDERER_INCLUDED_
#define _VIEW_SFML_HUBRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Station/Hub.hpp"


namespace View
{
    namespace SFML
    {
        class HubRenderer : public AUnorderedRenderer< Model::Hub >, public sf::Drawable
        {
        public:
            HubRenderer() {}
            virtual ~HubRenderer() {}
            virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const override;
        private:
        };
    }
}


#endif
