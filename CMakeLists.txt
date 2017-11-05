# This is the version I am currently using
# TODO check if older versions will work when this is completed
cmake_minimum_required(VERSION 3.7.2)
project(ProjectDemo)

# Requires OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

# Requires GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})

# Requires SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

# Requires Ryd3ngine
include_directories(${CMAKE_BINARY_DIR}/libs/Ryd3ngine/include)
link_directories(${CMAKE_BINARY_DIR}/libs/Ryd3ngine/lib)

# Create a list of all the files to use
set(SOURCE_FILES src/main.cpp)

# Place the output in lib
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Create the library
add_executable(ProjectDemo ${SOURCE_FILES})
target_link_libraries(ProjectDemo ${OPENGL_LIBRARIES})
target_link_libraries(ProjectDemo ${GLEW_LIBRARIES})
target_link_libraries(ProjectDemo ${SDL2_LIBRARIES})
target_link_libraries(ProjectDemo Ryd3ngine)
