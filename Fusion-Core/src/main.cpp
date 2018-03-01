/**
 * Test-bed for Fusion-Core
 * Used to test general component functionality
 *
 * Version: 0.0.1
 * Copyright 2017 Braxton Salyer
 *
 **/

#include "input/input.h"
#include "mathLibs/mathLib.h"
#include "utils/timer.h"
#include "graphics/color.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/window.h"
#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexbuffer.h"
#include "graphics/buffers/vertexarray.h"
#include "graphics/layers/tilelayer.h"
#include "graphics/renderables/renderable2D.h"
#include "graphics/renderables/static_sprite.h"
#include "graphics/renderables/sprite.h"
#include "graphics/renderers/simple2Drenderer.h"
#include "graphics/renderers/batchrenderer2D.h"
#include "graphics/ui/fusionbutton.h"
#include "graphics/ui/fusionmenu.h"
#include "graphics/ui/fusionwindow.h"
#include "graphics/ui/fusionUI.h"

#include <ctime>

using namespace fusion;
using namespace core;
using namespace math;
using namespace input;
using namespace graphics;
using namespace ui;

int main() {

    math::mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	FusionUI fusionUI = FusionUI();
/* no menu
	fusionUI.addWindow(new FusionWindow("Fusion", 800, 600, "src/shaders/basic.vert", "src/shaders/basic.frag", false));
*/

//create window
	fusionUI.addWindow(new FusionWindow("Fusion", 800, 600, "src/shaders/basic.vert", "src/shaders/basic.frag",true));

	FusionWindow* window = fusionUI.windowAt(0);

//create stuff for mainMenu
	Color colorOff = Color(math::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	Color colorNormal = Color(math::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Color colorHover = Color(math::vec4(0.35f, 0.35f, 0.35f, 1.0f));

//create menus
	FusionMenu* mainMenu =new FusionMenu(math::vec3(0.0f, 8.5f, 0.0f), math::vec2(16.0f, 0.5f), colorOff, colorNormal, colorHover,
								  MENU_STATE_NORMAL, MENU_TYPE_HORIZONTAL, 1, 2, true, fusionUI.windowAt(0)->getWindow());
	mainMenu->addButton(math::vec3(0.0f, 8.5f, 0.0f), math::vec2(1.0f, 0.5f));
	mainMenu->addButton(math::vec3(1.0f, 8.5f, 0.0f), math::vec2(15.0f, 0.5f));

	FusionMenu* vertMenu1 = new FusionMenu(math::vec3(0.0f, 8.0f, 0.0f), math::vec2(1.0f, 2.0f), colorOff, colorNormal, colorHover,
								  MENU_STATE_OFF, MENU_TYPE_VERTICAL, 1, 2, false, fusionUI.windowAt(0)->getWindow());
	vertMenu1->addButton(math::vec3(0.0f, 8.5f, 0.0f), math::vec2(1.0f, 0.5f));
	vertMenu1->addButton(math::vec3(0.0f, 8.0f, 0.0f), math::vec2(1.0f, 0.5f));

	FusionMenu* horzMenu1 = new FusionMenu(math::vec3(0.0f, 8.0f, 0.0f), math::vec2(4.0f, 0.5f), colorOff, colorNormal, colorHover,
								  MENU_STATE_OFF, MENU_TYPE_HORIZONTAL, 0, 2, false, fusionUI.windowAt(0)->getWindow());
	horzMenu1->addButton(math::vec3(0.0f, 8.0f, 0.0f), math::vec2(1.0f, 0.5f));
	horzMenu1->addButton(math::vec3(1.0f, 8.0f, 0.0f), math::vec2(3.0f, 0.5f));

	vertMenu1->addSubMenu(horzMenu1);
	
	mainMenu->addSubMenu(vertMenu1);

//add menu to window
	window->setMenu(mainMenu);

//activate renderer
	window->activateRenderer();

	Shader& shader = window->getShader();
    shader.setUniformMat4("pr_matrix", ortho);

	srand(time(NULL));
	Timer timer;
	float time = 0;
	int frames = 0;

	Texture* tex1 = new Texture("res/tex1.bmp");
	Texture* tex2 = new Texture("res/tex2.bmp");

	std::vector<Renderable2D*> sprites;
	int flip = 0;
	for (float y = 0; y < 9.0f; y += 0.5) {

		for (float x = 0; x < 16.0f; x += 0.5) {

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

	while (!window->getWindow()->closed()) {

    /*    double x, y;
		Mouse mouse = input::Mouse::GetInstance();
        mouse.getMousePosition(x, y);
		shader.setUniform2f("light_pos", math::vec2((float)(x * 16.0f/(float)window->getWidth()),
													(float)(9.0f - y * 9.0f/(float)window->getHeight())));
	*/
		shader.setUniform2f("light_pos", math::vec2(8.0f, 4.5f));
		for(int i = 0; i < sprites.size(); ++i) {

			window->addElement(sprites[i]);
		}

		window->update();

		frames++;
		if(timer.elapsed() - time > 1.0f) {

			time += 1.0f;
			printf("%dfps\n", frames);
			frames = 0;

		}

    } 

    return 0;
}
