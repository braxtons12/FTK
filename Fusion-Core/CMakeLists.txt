project(Fusion-Core)

set (GCC_COVERAGE_COMPILE_FLAGS "-g -std=gnu++11 -I../src -I../src/input -I../src/graphics -I../src/graphics/buffers -I../src/mathLibs -I../src/utils -lGL -lGLEW -lglfw")
set (GCC_COVERAGE_LINKER_FLAGS "-lGL -lGLEW -lglfw")

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINKER_FLAGS}" )

include_directories (include
                    src/
                    src/graphics/
                    src/graphics/buffers/
                    src/input/
                    src/mathLibs/
                    src/utils/ )

set ( GRAPHICS
    src/graphics/window.cpp
    src/graphics/shader.cpp
    src/graphics/buffers/buffer.cpp
    src/graphics/buffers/indexbuffer.cpp
    src/graphics/buffers/vertexarray.cpp
    src/graphics/renderable2D.h
    src/graphics/renderer2D.h
    src/graphics/static_sprite.cpp
    src/graphics/sprite.cpp
    src/graphics/simple2Drenderer.cpp
    src/graphics/batchrenderer2D.cpp )
set ( INPUT
    src/input/input.cpp )
set ( MATH
    src/mathLibs/mathLib.cpp )
set ( UTILS
    src/utils/fileutils.h )
set ( MAIN
    src/main.cpp )

set(EXECUTABLE_OUTPUT_PATH bin)
add_executable ( main ${MAIN} ${GRAPHICS} ${INPUT} ${MATH} ${UTILS} )

target_link_libraries( main
                    GL
                    GLEW
                    glfw
                    c )
