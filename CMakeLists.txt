cmake_minimum_required(VERSION 3.12)
project(Acryl)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

include_directories(${PROJECT_SOURCE_DIR}/external/include/)
include_directories(${PROJECT_SOURCE_DIR}/source/)

link_directories(${PROJECT_SOURCE_DIR}/external/lib/SDL2/)
link_directories(${PROJECT_SOURCE_DIR}/external/lib/GLEW/)

set(SOURCE_FILES
        source/main.cpp
    source/engine/window/window.h
    source/engine/window/window.cpp
    source/engine/util/util.h
    source/engine/util/util.cpp
    source/engine/opengl/shader/shader.h
    source/engine/opengl/shader/shader.cpp
    source/engine/opengl/vbo/vertexbufferobject.cpp
    source/engine/opengl/vbo/vertexbufferobject.cpp
    source/engine/opengl/texture/texture.cpp
    source/engine/opengl/texture/texture.h
    source/engine/math/transformation.cpp
    source/engine/math/transformation.h
    source/engine/math/camera.cpp
    source/engine/math/camera.h
    source/engine/pixelfield/pixelfield.cpp
    source/engine/pixelfield/pixelfield.h
    source/engine/acryl.h
    source/engine/defaults.h
    source/engine/renderer/tilemaprenderer.cpp
    source/engine/renderer/tilemaprenderer.h
        source/engine/math/cameracontroller2d.cpp source/engine/math/cameracontroller2d.h source/engine/opengl/framebuffer/framebuffer.cpp source/engine/opengl/framebuffer/framebuffer.h source/engine/renderer/framebufferrenderer.cpp source/engine/renderer/framebufferrenderer.h source/engine/gamelogic/acrylgame.cpp source/engine/gamelogic/acrylgame.h  source/game/testgame.cpp source/game/testgame.h source/game/world/tileworld.cpp source/game/world/tileworld.h source/engine/callbacks/Listener.h source/engine/callbacks/listener.h source/engine/callbacks/listener.cpp source/game/entity/player.cpp source/game/entity/player.h)

add_executable(acryl_bin ${SOURCE_FILES})
target_link_libraries(acryl_bin glew32 mingw32 SDL2main SDL2 SDL2_image SDL2_ttf opengl32)

#add_library(acryl SHARED ${SOURCE_FILES})
#target_link_libraries(acryl glew32 mingw32 SDL2main SDL2 SDL2_image SDL2_ttf opengl32)