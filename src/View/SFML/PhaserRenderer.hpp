#ifndef _VIEW_SFML_PHASERRENDERER_INCLUDED_
#define _VIEW_SFML_PHASERRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Station/Phaser.hpp"


namespace View
{
	namespace SFML
	{
        class PhaserRenderer : public AUnorderedRenderer< Model::Phaser >, public sf::Drawable
		{
		public:
            PhaserRenderer() {}
			virtual ~PhaserRenderer() {}
            virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const override;
		private:
		};
	}
}


#endif
