cmake_minimum_required(VERSION 3.7)
project(utilis)
if(ANDROID)
	set(CMAKE_CXX_FLAGS "-std=c++20")
	file(GLOB SOURCE_FILES
			./src/*/*.cpp
			./src/*.cpp
			)
	add_library(main STATIC ${SOURCE_FILES})
	find_library(nen nen)
	target_link_libraries(main nen)
	target_include_directories(main PUBLIC ./external/sinen/include)
elseif(EMSCRIPTEN)
	set(CMAKE_BUILD_TYPE_INIT "Release")
	set(CMAKE_C_COMPILER "emcc")
	file(GLOB SOURCE_FILES
			src/*/*.cpp
			src/*.cpp
	)
	add_executable(main ${SOURCE_FILES})
	target_link_directories(main PUBLIC
		.
		external/sinen/build/build
	)
	target_link_libraries(main nen lua)
	file(GLOB INCLUDE_DIRS
		external/sinen/include
		external/sinen/include/Nen
		)
	target_include_directories(main PUBLIC
		${INCLUDE_DIRS}
	)
	set(CMAKE_CXX_FLAGS
		"${CMAKE_CXX_FLAGS} -O2 \
		-s USE_SDL=2 \
		-s USE_SDL_IMAGE=2 \
		-s USE_WEBGL2=1 \
		-s FULL_ES3=1 \
		-s MIN_WEBGL_VERSION=2 \
		-s MAX_WEBGL_VERSION=2 \
		-s SDL2_IMAGE_FORMATS='[\"png\"]' \
		-s USE_BOOST_HEADERS=1 \
		-s USE_SDL_TTF=2 \
		-s USE_SDL_MIXER=2 \
		-s USE_SDL_NET=2 \
		--preload-file Assets \
		-s ALLOW_MEMORY_GROWTH \
		-std=c++20"
	)
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
set(CMAKE_CXX_FLAGS "-std=c++2a -Wno-subobject-linkage")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

find_package(Boost REQUIRED)
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
	./external/DTL/include
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
	${CMAKE_DL_LIBS}
)
endif(WIN32)
add_subdirectory(./external/sinen)

add_executable(sinen_game
	${SOURCE_FILES}
)
target_link_libraries(sinen_game 
	${LIBRARIES}
)
endif()
