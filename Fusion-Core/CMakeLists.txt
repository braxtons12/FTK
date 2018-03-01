project(Fusion-Core)

set (GCC_COVERAGE_COMPILE_FLAGS "-g -std=gnu++11 -I../src -I../src/input -I../src/graphics -I../src/graphics/buffers -I../src/graphics/layers -I../src/graphics/groups -I../src/mathLibs -I../src/utils -I../src/signals -lc -lGL -lGLEW -lglfw -lfreeimage -lfreetype -lftgl")
set (GCC_COVERAGE_LINKER_FLAGS "-lc -lGL -lGLEW -lglfw -lfreeimage -lfreetype -lftgl")

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINKER_FLAGS}" )

include_directories (include
                    src/
                    src/graphics/
                    src/graphics/buffers/
                    src/graphics/layers/
                    src/graphics/groups/
                    src/graphics/renderers/
                    src/graphics/renderables/
                    src/graphics/ui/
                    src/input/
                    src/mathLibs/
                    src/utils/ )

set ( GRAPHICS
    src/graphics/window.cpp
    src/graphics/shader.cpp
    src/graphics/buffers/buffer.cpp
    src/graphics/buffers/indexbuffer.cpp
    src/graphics/buffers/vertexarray.cpp
    src/graphics/layers/layer.cpp
    src/graphics/layers/tilelayer.cpp
    src/graphics/groups/group.cpp
    src/graphics/renderables/renderable2D.h
    src/graphics/renderers/renderer2D.h
    src/graphics/renderables/static_sprite.cpp
    src/graphics/renderables/sprite.cpp
    src/graphics/renderers/simple2Drenderer.cpp
    src/graphics/renderers/batchrenderer2D.cpp
    src/graphics/texture.cpp
    src/graphics/color.h
    src/graphics/ui/fusionwindow.cpp
    src/graphics/ui/fusionUI.cpp
    src/graphics/ui/fusionbutton.h
    src/graphics/ui/fusiontogglebutton.cpp
    src/graphics/ui/fusionmenu.cpp )
set ( INPUT
    src/input/input.cpp )
set ( MATH
    src/mathLibs/mathLib.cpp )
set ( SIGNALS
    src/signals/windowupdatesignal.cpp )
set ( UTILS
    src/utils/fileutils.h
    src/utils/imageload.h
    src/utils/timer.h )
set ( MAIN
    src/main.cpp )

set(EXECUTABLE_OUTPUT_PATH bin)
add_executable ( main ${MAIN} ${GRAPHICS} ${INPUT} ${MATH} ${SIGNALS} ${UTILS} )

target_link_libraries( main
                    GL
                    GLEW
                    glfw
                    freeimage
                    c )
