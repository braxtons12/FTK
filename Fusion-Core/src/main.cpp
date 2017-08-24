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
#include "../src/graphics/fusionwindow.h"
#include "../src/graphics/fusionUI.h"
#include "../src/utils/timer.h"
#include "../src/graphics/layers/tilelayer.h"

#include <time.h>
#include <pthread.h>

using namespace fusion;
using namespace core;
using namespace math;
using namespace graphics;
using namespace window;
using namespace input;

int main() {
	
	Window window("Sparky!", 960, 540);

    math::mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("../src/shaders/basic.vert", "../src/shaders/basic.frag");
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	
	TileLayer layer(&shader);
	for (float y = -9.0f; y < 9.0f; y += 0.05) {
		
		for (float x = -16.0f; x < 16.0f; x += 0.05) {
			
			layer.add(new Sprite(x, y, 0.04f, 0.04f, vec4(rand() % 1000/ 1000.0f, 0, 1, 1)));
		}
	}
	
	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	
	while (!window.closed()) {

		window.clear();
		double x, y;
		Mouse mouse = input::Mouse::GetInstance();
		mouse.getMousePosition(x, y);
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / window.getWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.getHeight())));
		
		window.update();
		frames++;
		if (time.elapsed() - timer > 1.0f) {
			
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
		
	}
	
	delete &shader;
	
	//old stuff. TODO update when FusionUI refactored for layer, transformation support
	 /*FusionUI fusionUI = FusionUI();
	fusionUI.addWindow(new FusionWindow("Fusion", 800, 600, "../src/shaders/basic.vert", "../src/shaders/basic.frag"));
	fusionUI.windowAt(0)->activateRenderer();

	Shader shader = fusionUI.windowAt(0)->getShader();
    shader.setUniformMat4("pr_matrix", ortho);
	
	srand(time(NULL));
	Timer timer;
	float time = 0;
	int frames = 0;
	
	std::vector<Renderable2D*> sprites;
	for (float y = 0; y < 9.0f; y += 0.05) {
		
		for (float x = 0; x < 16.0f; x += 0.05) {
			
			sprites.push_back(new Sprite(x, y, 0.04f, 0.04f, math::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			
		}
	}

    shader.setUniform2f("light_pos", math::vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", math::vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!fusionUI.windowAt(0)->getWindow()->closed()) {

        double x, y;
		Mouse* mouse = fusionUI.windowAt(0)->getMouse();
        mouse->getMousePosition(x, y);
		shader.setUniform2f("light_pos", math::vec2((float)(x * 16.0f/(float)fusionUI.windowAt(0)->getWidth()), 
													(float)(9.0f - y * 9.0f/(float)fusionUI.windowAt(0)->getHeight())));
		
		fusionUI.windowAt(0)->beginRenderer();
		
		for(int i = 0; i < sprites.size(); ++i) {
			
			fusionUI.windowAt(0)->addElement(sprites[i]);
		}
		
		fusionUI.windowAt(0)->update();
		
		frames++;
		if(timer.elapsed() - time > 1.0f) {
			
			time += 1.0f;
			printf("%dfps\n", frames);
			frames = 0;
			
		}
		
    } */

    return 0;
}
