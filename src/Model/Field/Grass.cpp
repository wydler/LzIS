#include "Grass.hpp"


using namespace Model::Field;


Grass::Grass()
{
}


Grass::~Grass()
{
}


bool Grass::contains( const glm::vec2 point ) const
{
    const float q2x = abs(point.x - position.x);
    const float q2y = abs(point.y - position.y);
    const float _hori = 17.3;
    const float _vert = 10.0;
    if (q2x > _hori || q2y > _vert*2)
        return false;
    return 2 * _vert * _hori - _vert * q2x - _hori * q2y >= 0;
}
