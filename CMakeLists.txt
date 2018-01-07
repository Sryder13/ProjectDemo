# This is the version I am currently using
# TODO check if older versions will work when this is completed
cmake_minimum_required(VERSION 3.7.2)
project(ProjectDemo)

# Need some extra modules for SDL2 Image and SDL2 Mixer
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakeModules/")

# include libs
include_directories(${CMAKE_SOURCE_DIR}/libs)

# Requires OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Requires GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

# Requires SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Requires SDL2 Image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

# Requires SDL2 Mixer
find_package(SDL2_mixer REQUIRED)
include_directories(${SDL2MIXER_INCLUDE_DIR})

# Requires Assimp
find_package(assimp REQUIRED)
include_directories(${assimp_INCLUDE_DIRS})

# Requires Ryd3ngine
include_directories(${CMAKE_SOURCE_DIR}/libs/Ryd3ngine/include)
link_directories(${CMAKE_SOURCE_DIR}/libs/Ryd3ngine/lib)

# Create a list of all the files to use
set(SOURCE_FILES	src/main.cpp
			src/player.cpp
			src/projectile.cpp
			src/enemy.cpp)

# Place the output in lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create the library
add_executable(ProjectDemo ${SOURCE_FILES})
target_link_libraries(ProjectDemo ${OPENGL_LIBRARIES})
target_link_libraries(ProjectDemo ${GLEW_LIBRARIES})
target_link_libraries(ProjectDemo ${SDL2_LIBRARIES})
target_link_libraries(ProjectDemo ${SDL2_IMAGE_LIBRARY})
target_link_libraries(ProjectDemo ${SDL2MIXER_LIBRARY})
target_link_libraries(ProjectDemo ${assimp_LIBRARIES})
target_link_libraries(ProjectDemo Ryd3ngine)
