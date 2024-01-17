#define STB_IMAGE_IMPLEMENTATION

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GlfwController.hpp"
#include "GlfwView.hpp"
#include "GlfwGame.hpp"


enum Renderer {
	OPENGL_GLFW,
	OPENGL_SDL
};

int main(int argc, char *argv[]) {
	Renderer mode = OPENGL_GLFW;

	// Represents the data model
	GlfwGame game;

	// manages user input
	GlfwController controller(game);

	// displays to screen
	GlfwView view(game, controller);
	view.initialize(); // OpenGL needs to init after object created

	// Now that an OpenGL context is open, initalize the game
	game.initialize();


	GLfloat currentTime = 0;
	GLfloat lastTime = 0;
	GLfloat deltaTime = 0;
	while (!view.getWindowShouldClose()) {
		//currentTime = glfwGetTimerValue();
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		// Take input from the Controller
		glfwPollEvents();
		controller.keyControl(deltaTime);
		controller.mouseControl();
		controller.mouseClickControl();

		// update game model
		game.update();

		// repaint the screen
		view.repaint();
		view.swapBuffers();
	}


	return 0;
}