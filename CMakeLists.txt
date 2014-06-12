cmake_minimum_required( VERSION 2.8 )
project( LzIS )

set( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH} )

file( GLOB_RECURSE HEADERS "src/*.hpp" )
set( EXECUTABLE_NAME "lzis" )
add_executable( ${EXECUTABLE_NAME}
	src/main.cpp
	src/Model/Updater.cpp
	src/Model/IntervalStepUpdater.cpp
	src/Model/Net/PulseDistributor.cpp
	src/Model/Station/Hub.cpp
	src/Model/Station/SolarPlant.cpp
	src/Model/Station/Phaser.cpp
	src/Model/Unit/Tank.cpp
        src/View/SFML/SceneManager.cpp
	src/View/SFML/AssetManager.cpp
	src/View/SFML/SolarPlantRenderer.cpp
	src/View/SFML/PhaserRenderer.cpp
	src/View/SFML/HubRenderer.cpp
	src/View/SFML/PulseLinkRenderer.cpp
	src/View/SFML/TankRenderer.cpp
        ${HEADERS}
)

# configure compiler for c++11 etc.
if( "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU" )
        set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++11 -std=c++0x" )
endif()

# wrap the main function for those OSes
if( ${CMAKE_SYSTEM_NAME} MATCHES "^Windows$|^Android$|^Darwin$" )
	set( NEED_MAIN_WRAP TRUE )
endif()

option( USE_SYSTEM_SFML "Use system SFML installation" OFF )
if( NOT USE_SYSTEM_SFML )
	set( BUILD_SHARED_LIBS FALSE CACHE BOOL "Build shared libraries" )
	add_subdirectory( "external/SFML" )
	include_directories( "${CMAKE_SOURCE_DIR}/external/SFML/include" )
	target_link_libraries( ${EXECUTABLE_NAME} sfml-system sfml-window sfml-graphics sfml-audio )
	if( NEED_MAIN_WRAP )
		target_link_libraries( ${EXECUTABLE_NAME} sfml-main )
	endif()
else()
	if( NEED_MAIN_WRAP )
		find_package( SFML 2 REQUIRED system window graphics network audio main )
	else()
		find_package( SFML 2 REQUIRED system window graphics network audio )
	endif()
	include_directories( ${SFML_INCLUDE_DIR} )
	target_link_libraries( ${EXECUTABLE_NAME} ${SFML_LIBRARIES} )
endif()

option( USE_SYSTEM_GLM "Use system GLM installation" OFF )
if( NOT USE_SYSTEM_GLM )
	include_directories( "${CMAKE_SOURCE_DIR}/external/glm/" )
endif()
