#ifndef _MODEL_ADESTROYABLE_INCLUDED_
#define _MODEL_ADESTROYABLE_INCLUDED_


#include <glm/vec2.hpp>

#include "APositionable2D.hpp"


enum LifeState
{
    SPAWNING,
    ALIVE,
    DYING,
    DEAD
};


namespace Model
{
    class ADestroyable : virtual public APositionable2D
    {
    public:
        virtual LifeState getState() const { return this->state; }
        virtual double getLife() const = 0;
        virtual void hit( const double damage ) = 0;
    protected:
        LifeState state = LifeState::ALIVE;
    };
}


#endif
