#ifndef _VIEW_SFML_SCENEMANAGER_INCLUDED_
#define _VIEW_SFML_SCENEMANAGER_INCLUDED_


#include <set>

#include "SolarPlantRenderer.hpp"
#include "PhaserRenderer.hpp"
#include "HubRenderer.hpp"
#include "TankRenderer.hpp"
#include "PulseLinkRenderer.hpp"
#include "FieldRenderer.hpp"
#include "../ADrawable.hpp"
#include "../../Model/ADestroyable.hpp"


namespace View
{
    namespace SFML
    {
        class SceneManager : public sf::Drawable
        {
        public:
            static SceneManager * instance()
            {
                static CGuard g;
                if (!_instance)
                    _instance = new SceneManager();
                return _instance;
            }

            virtual void draw( sf::RenderTarget & target, sf::RenderStates states ) const override;

            std::set< Model::ADestroyable * > & getEnemies() { return enemies; }
            Model::ADestroyable * getNextEnemy( glm::vec2 pos, double maxDistance );

            View::SFML::EnemyRenderer * getEnemyRenderer() { return this->enemyRenderer; }
            void setTankRenderer( View::SFML::EnemyRenderer * renderer ) { this->enemyRenderer = renderer; }

            std::set< Model::SolarPlant * > & getSolarPlants() { return solarPlants; }
            View::SFML::SolarPlantRenderer * getSolarPlantRenderer() { return this->solarPlantRenderer; }

            std::set< Model::Phaser * > & getPhasers() { return phasers; }
            View::SFML::PhaserRenderer * getPhaserRenderer() { return this->phaserRenderer; }

            std::set< Model::Hub * > & getHubs() { return hubs; }
            View::SFML::HubRenderer * getHubRenderer() { return this->hubRenderer; }

            std::set< Model::Net::PulseLink * > & getLinks() { return links; }
            View::SFML::PulseLinkRenderer * getPulseLinkRenderer() { return this->pulseLinkRenderer; }

            std::set< Model::AField2D * > & getFields() { return fields; }
            View::SFML::FieldRenderer * getFieldRenderer() { return this->fieldRenderer; }
            Model::AField2D * getFieldAt( const glm::vec2 & pos );
            std::set< Model::AField2D * > & getNextFieldsTo( Model::AField2D * field, const int level );
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
            std::set< Model::SolarPlant * > solarPlants;
            std::set< Model::Phaser * > phasers;
            std::set< Model::Hub * > hubs;
            std::set< Model::Net::PulseLink * > links;
            std::set< Model::AField2D * > fields;

            View::SFML::EnemyRenderer * enemyRenderer;
            View::SFML::SolarPlantRenderer * solarPlantRenderer;
            View::SFML::PhaserRenderer * phaserRenderer;
            View::SFML::HubRenderer * hubRenderer;
            View::SFML::PulseLinkRenderer * pulseLinkRenderer;
            View::SFML::FieldRenderer * fieldRenderer;
        };
    }
}


#endif
