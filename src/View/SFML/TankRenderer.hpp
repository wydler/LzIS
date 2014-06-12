#ifndef _VIEW_SFML_TANKRENDERER_INCLUDED_
#define _VIEW_SFML_TANKRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Unit/Tank.hpp"


namespace View
{
    namespace SFML
    {
        class TankRenderer : public AUnorderedRenderer< Model::Tank >
        {
        public:
            TankRenderer( sf::RenderWindow & window ) : window(window) {}
            virtual ~TankRenderer() {}
            virtual void draw() const override;
        private:
            sf::RenderWindow & window;
        };
    }
}


#endif
