cmake_minimum_required(VERSION 3.12)
project(Acryl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(${PROJECT_SOURCE_DIR}/external/include/)

link_directories(${PROJECT_SOURCE_DIR}/external/lib/SDL2/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/GLEW/)

file(GLOB_RECURSE SOURCE_FILES source/*)

add_executable(Acryl ${SOURCE_FILES})

target_link_libraries(Acryl glew32 mingw32 SDL2main SDL2 SDL2_image SDL2_ttf opengl32)