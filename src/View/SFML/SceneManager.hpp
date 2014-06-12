#ifndef _VIEW_SFML_SCENEMANAGER_INCLUDED_
#define _VIEW_SFML_SCENEMANAGER_INCLUDED_


#include <set>

#include "TankRenderer.hpp"
#include "../ADrawable.hpp"
#include "../../Model/ADestroyable.hpp"


namespace View
{
    namespace SFML
    {
        class SceneManager
        {
        public:
            static SceneManager * instance()
            {
                static CGuard g;
                if (!_instance)
                    _instance = new SceneManager();
                return _instance;
            }

            std::set< Model::ADestroyable * > * getEnemies() { return & this->enemies; }
            Model::ADestroyable * getNextEnemy( glm::vec2 pos, double maxDistance );

            View::SFML::TankRenderer * getTankRenderer() { return this->tankRenderer; }
            void setTankRenderer( View::SFML::TankRenderer * renderer ) { this->tankRenderer = renderer; }
        private:
            SceneManager();
            SceneManager( const SceneManager & ) {}
            ~SceneManager() {}
            class CGuard
            {
            public:
                ~CGuard()
                {
                    if( NULL != SceneManager::_instance )
                    {
                        delete SceneManager::_instance;
                        SceneManager::_instance = NULL;
                    }
                }
            };
            friend class CGuard;

            static SceneManager * _instance;

            std::set< Model::ADestroyable * > enemies;

            View::SFML::TankRenderer * tankRenderer;
        };
    }
}


#endif
