#ifndef _MODEL_FIELD_GRASS_HPP
#define _MODEL_FIELD_GRASS_HPP


#include "../AField2D.hpp"


namespace Model
{
    namespace Field
    {
        class Grass : public AField2D
        {
        public:
            Grass();
            virtual ~Grass();

            virtual bool contains( const glm::vec2 point ) const;

            virtual glm::vec2 getPosition() const { return this->position; }
            virtual void setPosition( const glm::vec2 & position ) { this->position = position; }

            virtual FieldState getState() const { return state; }
            virtual void setState( FieldState state ) { this->state = state; }
        private:
            glm::vec2 position = glm::vec2( 0, 0 );
            FieldState state = FieldState::IDLE;
        };
    }
}


#endif // _MODEL_FIELD_GRASS_HPP
