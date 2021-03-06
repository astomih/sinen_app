cmake_minimum_required(VERSION 3.7)
project(model_converter)
set(CMAKE_CXX_FLAGS "-std=c++2a")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)


file(GLOB SOURCE_FILES
	./src/*/*.cpp 
	./src/*.cpp
)

include_directories(
	../external/sinen/include
	../external/sinen/include/Nen
)
link_directories(
	../external/sinen/build
)
find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenAL REQUIRED)
find_package(assimp REQUIRED)
add_subdirectory(./external/sinen)
set(LIBRARIES
	nen
    assimp
	${Vulkan_LIBRARIES}	
	SDL2
	SDL2main
	SDL2_image
	SDL2_mixer
	SDL2_ttf
	SDL2_net
	openal
	glew32
	opengl32
)

add_executable(model_converter
	${SOURCE_FILES}
)
target_link_libraries(model_converter 
	${LIBRARIES}
)
