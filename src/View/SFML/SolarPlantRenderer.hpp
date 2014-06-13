#ifndef _VIEW_SFML_SOLARPLANTRENDERER_INCLUDED_
#define _VIEW_SFML_SOLARPLANTRENDERER_INCLUDED_


#include <SFML/Graphics.hpp>

#include "../AUnorderedRenderer.hpp"
#include "../../Model/Station/SolarPlant.hpp"


namespace View
{
	namespace SFML
	{
        class SolarPlantRenderer : public AUnorderedRenderer< Model::SolarPlant >, public sf::Drawable
		{
		public:
            SolarPlantRenderer() {}
			virtual ~SolarPlantRenderer() {}

            virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const override;
		private:
		};
	}
}


#endif
