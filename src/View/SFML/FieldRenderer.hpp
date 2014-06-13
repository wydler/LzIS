#ifndef _VIEW_SFML_FIELDRENDERER_INCLUDED_
#define _VIEW_SFML_FIELDRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/AField2D.hpp"


namespace View
{
    namespace SFML
    {
        class FieldRenderer : public AUnorderedRenderer< Model::AField2D >, public sf::Drawable
        {
        public:
            FieldRenderer() {}
            virtual ~FieldRenderer() {}

            virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const override;
        private:
        };
    }
}


#endif
