/**
 * Test-bed for Fusion-Core
 * Used to test general component functionality
 *
 * Version: 0.0.1
 * Copyright 2017 Braxton Salyer
 *
 **/

#include "../src/graphics/window.h"
#include "../src/mathLibs/mathLib.h"
#include "../src/utils/timer.h"
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
#include "../src/graphics/layers/tilelayer.h"
#include "../src/graphics/texture.h"
#include "../src/graphics/fusionmenu.h"
#include "../src/graphics/fusionbutton.h"

#include <ctime>
#include <pthread.h>

using namespace fusion;
using namespace core;
using namespace math;
using namespace graphics;
using namespace window;
using namespace input;

int main() {

    math::mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	FusionUI fusionUI = FusionUI();
/* no menu
	fusionUI.addWindow(new FusionWindow("Fusion", 800, 600, "src/shaders/basic.vert", "src/shaders/basic.frag", false));
*/

//menu
	Texture* menuOff = new Texture("res/menus/main_off.png");
	Texture* menuHover = new Texture("res/menus/main_hover.png");
	std::vector<float>* menuDivisions = new std::vector<float>();
	menuDivisions->push_back(0.0f);
	menuDivisions->push_back(16.0f);
	std::vector<FusionMenu>* otherMenus = new std::vector<FusionMenu>();

	fusionUI.addWindow(new FusionWindow("Fusion", 800, 600, "src/shaders/basic.vert", "src/shaders/basic.frag", true));
	fusionUI.windowAt(0)->setMenu(new FusionMenu(math::vec3(0.0f, 0.8f, 0.0f), math::vec2(0.9f, 0.9f), math::vec4(0.5, 0.5, 0.5, 1), menuOff, menuHover, menuOff,
                               MENU_STATE_NORMAL, MENU_TYPE_HORIZONTAL, *menuDivisions, 0, 1, fusionUI.windowAt(0)->getWindow()));
	fusionUI.windowAt(0)->getMenu()->addButton(math::vec3(0.0f, 0.8f, 0.0f), math::vec2(0.9f, 0.9f));
	fusionUI.windowAt(0)->activateRenderer();

	Shader& shader = fusionUI.windowAt(0)->getShader();
    shader.setUniformMat4("pr_matrix", ortho);

	srand(time(NULL));
	Timer timer;
	float time = 0;
	int frames = 0;

	Texture* tex1 = new Texture("res/tex1.bmp");
	Texture* tex2 = new Texture("res/tex2.bmp");

	std::vector<Renderable2D*> sprites;
	int flip = 0;
	for (float y = 0; y < 9.0f; y += 0.05) {

		for (float x = 0; x < 16.0f; x += 0.05) {

			if(!(flip % 2)) sprites.push_back(new Sprite(x, y, 0.9f, 0.9f, tex1));
			else sprites.push_back(new Sprite(x, y, 0.9f, 0.9f, tex2));
			++flip;
		}
		++flip;
	}

    shader.setUniform2f("light_pos", math::vec2(4.0f, 1.5f));
	GLint* texIDs = new GLint[32];
	for(int i = 0; i < 32; ++i) {
		texIDs[i] = i;
	}
	shader.setUniform1iv("textures", texIDs, 32);

	BatchRenderer2D* renderer = new BatchRenderer2D();

	while (!fusionUI.windowAt(0)->getWindow()->closed()) {

        double x, y;
		Mouse mouse = input::Mouse::GetInstance();
        mouse.getMousePosition(x, y);
		shader.setUniform2f("light_pos", math::vec2((float)(x * 16.0f/(float)fusionUI.windowAt(0)->getWidth()),
													(float)(9.0f - y * 9.0f/(float)fusionUI.windowAt(0)->getHeight())));


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

    } 

    return 0;
}
