#ifndef _MODEL_PHASER_INCLUDED_
#define _MODEL_PHASER_INCLUDED_


#include "../APositionable2D.hpp"
#include "../ABoundingBox2D.hpp"
#include "../AUpdateable.hpp"
#include "../ADestroyable.hpp"
#include "../AStepUpdateable.hpp"
#include "../Net/APulseConsumer.hpp"
#include "../Net/PulseNode.hpp"
#include "../Unit/Tank.hpp"


namespace Model
{
    class Phaser : public AUpdateable, public AStepUpdateable, public Net::APulseConsumer, public APositionable2D, public ABoundingBox2D
	{
	public:
		Phaser();
		virtual ~Phaser();

		virtual void update( double delta ) override;
        virtual void step() override;

		virtual Net::PulseNode * getNode() override { return this->node; }

        virtual bool isPulseNeeded() const override { return this->pulses < 5; }
        virtual bool givePulse() { this->pulses++; return true; }
		virtual int getPriority() const override { return 0; }

		virtual glm::vec2 getPosition() const { return this->position; }
		virtual void setPosition( const glm::vec2 & position ) { this->position = position; this->node->setPosition( position ); }

        virtual glm::vec2 getMaxCorner() const { return this->position + glm::vec2( 15, 15 ); }
        virtual glm::vec2 getMinCorner() const { return this->position - glm::vec2( 15, 15 ); }

		void setPulses( unsigned int pulses ) { this->pulses = pulses; }
        unsigned int getPulses() const { return this->pulses; }

        ADestroyable * getEnemy() const { return this->target; }

	private:
		Net::PulseNode * node = nullptr;
        Model::ADestroyable * target = nullptr;
		unsigned int pulses = 0;
		glm::vec2 position = glm::vec2(0,0);
	};
}

#endif
