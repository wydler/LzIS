#ifndef _MODEL_TANK_INCLUDED_
#define _MODEL_TANK_INCLUDED_


#include "../APositionable2D.hpp"
#include "../ABoundingBox2D.hpp"
#include "../AUpdateable.hpp"
#include "../ADestroyable.hpp"


namespace Model
{
    class Tank : public AUpdateable, public ADestroyable, public ABoundingBox2D
    {
    public:
        Tank();
        virtual ~Tank();

        virtual void update( double delta ) override;

        virtual double getLife() const { return this->life; }
        virtual void hit( const double damage );

        virtual glm::vec2 getPosition() const { return this->position; }
        virtual void setPosition( const glm::vec2 & position ) { this->position = position; }

        virtual glm::vec2 getMaxCorner() const { return this->position + glm::vec2( 15, 15 ); }
        virtual glm::vec2 getMinCorner() const { return this->position - glm::vec2( 15, 15 ); }
    private:
        glm::vec2 position = glm::vec2(0,0);
        double timer = 5.0;
        double life = 100.0;
    };
}


#endif
