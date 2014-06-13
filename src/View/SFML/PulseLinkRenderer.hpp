#ifndef _VIEW_SFML_PULSELINKRENDERER_INCLUDED_
#define _VIEW_SFML_PULSELINKRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Net/PulseLink.hpp"


namespace View
{
	namespace SFML
	{
        class PulseLinkRenderer : public AUnorderedRenderer< Model::Net::PulseLink >, public sf::Drawable
		{
		public:
            PulseLinkRenderer() {}
			virtual ~PulseLinkRenderer() {}
            virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const override;
		private:
		};
	}
}


#endif
