#ifndef _MODEL_AFIELD2D_HPP
#define _MODEL_AFIELD2D_HPP


#include "APositionable2D.hpp"


enum FieldState
{
    IDLE,
    HOVER,
    ACTIVE
};


namespace Model
{
    class AField2D : virtual public APositionable2D
    {
    public:
        virtual bool contains( const glm::vec2 point ) const = 0;

        virtual FieldState getState() const = 0;
        virtual void setState( FieldState state ) = 0;
    };
}


#endif // _MODEL_AFIELD2D_HPP
