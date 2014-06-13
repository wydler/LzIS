#ifndef _VIEW_SFML_TANKRENDERER_INCLUDED_
#define _VIEW_SFML_TANKRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Unit/Tank.hpp"


namespace View
{
    namespace SFML
    {
        class EnemyRenderer : public AUnorderedRenderer< Model::Tank >, public sf::Drawable
        {
        public:
            EnemyRenderer() {}
            virtual ~EnemyRenderer() {}
            virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const override;
        private:
        };
    }
}


#endif
