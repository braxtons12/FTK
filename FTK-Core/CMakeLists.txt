cmake_minimum_required(VERSION 3.0)
project(FTK-Core)
set(cxxClang FALSE)
#set(CMAKE_EXPORT_COMPILE_COMMANDS YES)
if(cxxClang)
	set(CMAKE_CXX_COMPILER clang++)
	set (COVERAGE_LINKER_FLAGS "-lc -lGL -lGLEW -lglfw -lfreeimage -lfreetype -lftgl")
	set (COVERAGE_COMPILE_FLAGS "-g -std=c++17 -I../src -I../src/input -I../src/graphics -I../src/graphics/ui -I../src/graphics/renderers -I../src/graphics/renderables -I../src/graphics/buffers -I../src/graphics/layers -I../src/graphics/groups -I../src/mathLibs -I../src/utils -I../src/signals -I/usr/include/freetype2 -I../ext ${COVERAGE_LINKER_FLAGS}")
else(cxxClang)
	set(CMAKE_CXX_COMPILER g++)
	set(COVERAGE_LINKER_FLAGS "-lc -lGL -lGLEW -lglfw -lfreeimage -lfreetype -lftgl")
	set(COVERAGE_COMPILE_FLAGS "-g -std=gnu++17 -Wno-invalid-offsetof -I../src -I../src/input -I../src/graphics -I../src/graphics/ui -I../src/graphics/renderers -I../src/graphics/renderables -I../src/graphics/buffers -I../src/graphics/layers -I../src/graphics/groups -I../src/mathLibs -I../src/utils -I../src/signals -I/usr/include/freetype2 -I../ext ${COVERAGE_LINKER_FLAGS}")
endif(cxxClang)
SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${COVERAGE_LINKER_FLAGS}" )

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
set ( BASE
	src/base/ftkobject.cpp )
set ( GRAPHICS
    src/graphics/nativewindow.cpp
    src/graphics/shader.cpp
    src/graphics/buffers/buffer.cpp
    src/graphics/buffers/indexbuffer.cpp
    src/graphics/buffers/vertexarray.cpp
    src/graphics/layers/layer.cpp
    src/graphics/layers/tilelayer.cpp
    src/graphics/groups/group.cpp
    src/graphics/renderables/renderable2D.h
    src/graphics/renderables/static_sprite.cpp
    src/graphics/renderables/sprite.cpp
    src/graphics/renderables/label.cpp
    src/graphics/renderers/renderer2D.h
    src/graphics/renderers/simple2Drenderer.cpp
    src/graphics/renderers/batchrenderer2D.cpp
    src/graphics/texture.cpp
    src/graphics/color.h
    src/graphics/ui/ftkwindow.cpp
    src/graphics/ui/ftkUI.cpp
    src/graphics/ui/ftkbutton.h
    src/graphics/ui/ftktogglebutton.cpp
    src/graphics/ui/ftkmenu.cpp )
set ( INPUT
    src/input/input.cpp )
set ( MATH
    src/mathLibs/mathLib.cpp )
set ( SIGNALS
    src/signals/signal.h )
set ( UTILS
    src/utils/fileutils.h
    src/utils/imageload.h
    src/utils/timer.h )
set ( MAIN
    src/main.cpp )

set(EXECUTABLE_OUTPUT_PATH bin)
add_executable ( main ${MAIN} ${BASE} ${GRAPHICS} ${INPUT} ${MATH} ${SIGNALS} ${UTILS} )

target_link_libraries( main
                    GL
                    GLEW
                    glfw
                    freeimage
                    freetype
                    ftgl
                    c )
