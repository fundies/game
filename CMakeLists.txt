cmake_minimum_required(VERSION 3.6)

project(Platformer)

set(EXECUTABLE_NAME "GAYM")

#add includes
if (ANDROID)
  set(GLAD_DIR glad/gles2/)
else()
  set(GLAD_DIR glad/gles3/)
endif()

include_directories(
 .
 "src/" 
 "game/"
 "${GLAD_DIR}/include"
 "Crash2D/library/include"
 "tmx/src/"
)

#link_directories(AFTER /mingw64/lib)

#add sources
file(GLOB ENGINE_SOURCES "src/*.cpp" "src/*.c")
file(GLOB GAME_SOURCES "game/*.cpp")
file(GLOB CRASH2D_SOURCES "Crash2D/library/src/*.cpp")
file(GLOB TMX_SOURCES "tmx/src/*.c")

set(GLAD_SOURCES "${GLAD_DIR}/src/glad.c")
set(CMAKE_CXX_STANDARD 17)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 sdl2)
include_directories("${SDL2_INCLUDE_DIRS}")

PKG_SEARCH_MODULE(SDL_IMAGE SDL2_image)
include_directories("${SDL_IMAGE_INCLUDE_DIRS}")

find_path(tinyxml2_INCLUDE_DIR NAMES tinyxml2.h)
find_library(TINYXML2_LIBRARIES NAMES tinyxml2)
include_directories("${tinyxml2_INCLUDE_DIR}")

find_package(LibXml2 REQUIRED)
include_directories("${LIBXML2_INCLUDE_DIRS}")

add_executable(${EXECUTABLE_NAME} ${GLAD_SOURCES} ${CRASH2D_SOURCES} ${TMX_SOURCES} ${ENGINE_SOURCES} ${GAME_SOURCES} "main.cpp")

target_link_libraries(${EXECUTABLE_NAME} ${SDL2_LIBRARIES} ${SDL_IMAGE_LIBRARIES} ${TINYXML2_LIBRARIES} ${LIBXML2_LIBRARIES})

  
target_compile_definitions(${EXECUTABLE_NAME} PRIVATE RES_W=1920 RES_H=1080)
