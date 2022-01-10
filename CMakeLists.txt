cmake_minimum_required(VERSION 3.7)
project(sinen_game)


set(CMAKE_CXX_FLAGS "-std=c++2a -Wno-subobject-linkage")
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)
find_package(OpenAL REQUIRED)


file(GLOB SOURCE_FILES
	./src/*/*.cpp 
	./src/*.cpp
)

include_directories(
	./external/sinen/include
)
link_directories(
	./external/sinen/build
)
if(WIN32)
set(LIBRARIES
	nen
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
else()
set(LIBRARIES
	nen
	${Vulkan_LIBRARIES}	
	SDL2
	SDL2main
	SDL2_image
	SDL2_mixer
	SDL2_ttf
	SDL2_net
	openal
	GLEW
	GL
)
endif(WIN32)

add_executable(sinen_game
	${SOURCE_FILES}
)
target_link_libraries(sinen_game 
	${LIBRARIES}
)
