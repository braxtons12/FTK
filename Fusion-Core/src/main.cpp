#include "../src/graphics/window.h"
#include "../src/mathLibs/mathLib.h"
#include "../src/graphics/shader.h"
#include "../src/graphics/buffers/buffer.h"
#include "../src/graphics/buffers/indexbuffer.h"
#include "../src/graphics/buffers/vertexarray.h"
#include "../src/input/input.h"
#include "../src/graphics/renderable2D.h"
#include "../src/graphics/static_sprite.h"
#include "../src/graphics/sprite.h"
#include "../src/graphics/simple2Drenderer.h"
#include "../src/graphics/batchrenderer2D.h"

int main() {

    using namespace fusion;
    using namespace core;
    using namespace window;
    using namespace graphics;
    using namespace input;

    Window window("Sparky!", 800, 600);
    //glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    Shader shader("../src/shaders/basic.vert", "../src/shaders/basic.frag");
    shader.enable();

    shader.setUniformMat4("pr_matrix", ortho);

    Sprite sprite1(5, 5, 4, 4, math::vec4(1, 0, 1 ,1));
    Sprite sprite2(7, 1, 2, 3, math::vec4(0.2f, 0, 1 ,1));
    BatchRenderer2D renderer;

    shader.setUniform2f("light_pos", math::vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", math::vec4(0.2f, 0.3f, 0.8f, 1.0f));

    while (!window.closed()) {
        
        window.clear();

        double x, y;
        Mouse& mouse = Mouse::GetInstance();
        mouse.getMousePosition(x, y);
        shader.setUniform2f("light_pos", math::vec2((float)(x * 16.0f/800.0f), (float)(9.0f - y * 9.0f/600.0f)));
		renderer.begin();
        renderer.submit(&sprite1);
        renderer.submit(&sprite2);
		renderer.end();
        renderer.flush();
    
        window.update();
    }

    return 0;
}
