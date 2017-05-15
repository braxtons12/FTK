#include "../src/graphics/window.h"
#include "../src/mathLibs/mathLib.h"
#include "../src/graphics/shader.h"
#include "../src/graphics/buffers/buffer.h"
#include "../src/graphics/buffers/indexbuffer.h"
#include "../src/graphics/buffers/vertexarray.h"
#include "../src/input/input.h"
#include "../src/graphics/renderable2D.h"
#include "../src/graphics/simple2Drenderer.h"

int main() {

    using namespace fusion;
    using namespace core;
    using namespace window;
    using namespace graphics;
    using namespace input;

    Window window("Sparky!", 800, 600);
    //glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

    math::mat4 ortho = math::mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

    Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
    shader.enable();

    shader.setUniformMat4("pr_matrix", ortho);
    shader.setUniformMat4("ml_matrix", math::mat4::translation(math::vec3(4,3,0)));

    Renderable2D sprite1(math::vec3(5, 5, 0), math::vec2(4, 4), math::vec4(1, 0, 1 ,1), shader);
    Renderable2D sprite2(math::vec3(7, 1, 0), math::vec2(2, 3), math::vec4(0.2f, 0, 1 ,1), shader);
    Simple2DRenderer renderer;

    shader.setUniform2f("light_pos", math::vec2(4.0f, 1.5f));

    while (!window.closed()) {
        
        window.clear();

        double x, y;
        Mouse& mouse = Mouse::GetInstance();
        mouse.getMousePosition(x, y);
        shader.setUniform2f("light_pos", math::vec2((float)(x * 16.0f/800.0f), (float)(9.0f - y * 9.0f/600.0f)));
        renderer.submit(&sprite1);
        renderer.submit(&sprite2);
        renderer.flush();
    
        window.update();
    }

    return 0;
}