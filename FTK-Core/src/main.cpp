/**
 * Test-bed for Ftk-Core
 * Used to test general component functionality
 *
 * Version: 0.0.1
 * C 2018 Braxton Salyer
 *
 **/

#include "input/input.h"
#include "mathLibs/mathLib.h"
#include "utils/timer.h"
#include "graphics/color.h"
#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/nativewindow.h"
#include "graphics/buffers/buffer.h"
#include "graphics/buffers/indexbuffer.h"
#include "graphics/buffers/vertexarray.h"
#include "graphics/layers/tilelayer.h"
#include "graphics/renderables/renderable2D.h"
#include "graphics/renderables/static_sprite.h"
#include "graphics/renderables/sprite.h"
#include "graphics/renderers/simple2Drenderer.h"
#include "graphics/renderers/batchrenderer2D.h"
#include "graphics/ui/ftkbutton.h"
#include "graphics/ui/ftkmenu.h"
#include "graphics/ui/ftkwindow.h"
#include "graphics/ui/ftkUI.h"

#include <ctime>

using namespace ftk;
using namespace core;
using namespace math;
using namespace input;
using namespace graphics;
using namespace ui;

int main() {

	FtkUI ftkUI = FtkUI();

	//create window
	ftkUI.addWindow(new FtkWindow("Ftk", 800, 600, "src/shaders/basic.vert", "src/shaders/basic.frag"));

	FtkWindow* window = ftkUI.windowAt(0);

	math::mat4 ortho = mat4::orthographic(0.0f, window->getWidth(), 0.0f, window->getHeight(), -1.0f, 1.0f);

	//create stuff for mainMenu
	Color colorOff = Color(math::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	Color colorNormal = Color(math::vec4(0.2f, 0.2f, 0.2f, 1.0f));
	Color colorHover = Color(math::vec4(0.35f, 0.35f, 0.35f, 1.0f));

	float menuHeight = window->getHeight()/18;	
	float menu1Y = menuHeight;
	float menu2Y = 2 * menuHeight;
	float menuWidth = window->getWidth();
	float buttonWidth = window->getWidth()/16;
	float buttonHeight = menuHeight;

	//create menus
	FtkMenu* mainMenu = new FtkMenu(math::vec3(0.0f, menu1Y, 0.0f), math::vec2(menuWidth, menuHeight), colorOff, colorNormal, colorHover,
								  MENU_STATE_NORMAL, MENU_TYPE_HORIZONTAL, true, window->getWindow());
	mainMenu->addButton(math::vec3(0.0f, menu1Y, 0.0f), math::vec2(buttonWidth, buttonHeight));
	mainMenu->addButton(math::vec3(buttonWidth, menu1Y, 0.0f), math::vec2(menuWidth - buttonWidth, buttonHeight));

	FtkMenu* vertMenu1 = new FtkMenu(math::vec3(0.0f, menu2Y, 0.0f), math::vec2(buttonWidth, 2 * buttonHeight), colorOff, colorNormal, colorHover,
								  MENU_STATE_OFF, MENU_TYPE_VERTICAL, false, window->getWindow());
	vertMenu1->addButton(math::vec3(0.0f, menu1Y, 0.0f), math::vec2(buttonWidth, buttonHeight));
	vertMenu1->addButton(math::vec3(0.0f, menu2Y, 0.0f), math::vec2(buttonWidth, buttonHeight));

	FtkMenu* horzMenu1 = new FtkMenu(math::vec3(0.0f, menu2Y, 0.0f), math::vec2(4 * buttonWidth, buttonHeight), colorOff, colorNormal, colorHover,
								  MENU_STATE_OFF, MENU_TYPE_HORIZONTAL, false, window->getWindow());
	horzMenu1->addButton(math::vec3(0.0f, menu2Y, 0.0f), math::vec2(buttonWidth, buttonHeight));
	horzMenu1->addButton(math::vec3(buttonWidth, menu2Y, 0.0f), math::vec2(3 * buttonWidth, buttonHeight));

	vertMenu1->addSubMenu(horzMenu1);
	
	mainMenu->addSubMenu(vertMenu1);

	//add menu to window
	window->setMenu(mainMenu);

	//activate renderer
	window->activateRenderer();

	Shader shader = window->getShader();
    shader.setUniformMat4("pr_matrix", ortho);

	srand(time(NULL));
	Timer timer;
	float updateTime = 0;
	float frameTime = 0;
	float frameTimer = (1.0f / 120.0f);

	int frames = 0;

	Texture* tex1 = new Texture("res/tex1.bmp");
	Texture* tex2 = new Texture("res/tex2.bmp");

	float spriteY = window->getHeight() / 36;
	float spriteX = window->getWidth() / 64;
	std::vector<Renderable2D*> sprites;
	int flip = 0;
	for (float y = 0; y < window->getHeight(); y += spriteY) {

		for (float x = 0; x < window->getWidth(); x += spriteX) {

			if(!(flip % 2)) sprites.push_back(new Sprite(x, y, 0.9f * spriteX, 0.9f * spriteY, tex1));
			else sprites.push_back(new Sprite(x, y, 0.9f * spriteX, 0.9f * spriteY, tex2));
			++flip;
		}
		++flip;
	}

	GLint* texIDs = new GLint[32];
	for(int i = 0; i < 32; ++i) {
		texIDs[i] = i;
	}
	shader.setUniform1iv("textures", texIDs, 32);

	while (!window->closed()) {
		
		/*
		double x, y;
		Mouse mouse = input::Mouse::GetInstance();
        mouse.getMousePosition(x, y);
		y = window->getHeight() - y;
		window->getWindow()->convertCoords(x, y);
		shader.setUniform2f("light_pos", math::vec2(x, y));
		*/

		window->update();
		//if(timer.elapsed() - updateTime > frameTimer) {
			for(int i = 0; i < sprites.size(); ++i) {

				window->addElement(sprites[i]);
			}
			window->clear();
			window->beginRender();
			
			ortho = mat4::orthographic(0.0f, window->getWidth(), 0.0f, window->getHeight(), -1.0f, 1.0f);
			shader.setUniformMat4("pr_matrix", ortho);
			window->render();
			
			updateTime += frameTimer;
			frames++;
		//}

		if(timer.elapsed() - frameTime > 1.0f) {

			frameTime += 1.0f;
			printf("%dfps\n", frames);
			frames = 0;
		}

    } 

    return 0;
}
