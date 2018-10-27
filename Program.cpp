/*
 * Program.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#include "Program.h"

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "RenderingEngine.h"
#include "Scene.h"

Scene* currentScene;

int partNumber = 0;

Program::Program() {
	setupWindow();
}

Program::~Program() {
	//Must be cleaned up in the destructor because these are allocated to the heap
	delete renderingEngine;
	delete scene;
}

void Program::start() {
	renderingEngine = new RenderingEngine();
	scene = new Scene(renderingEngine);
	//scene->initializeScene();

	currentScene = scene;
	scene->drawScene();

	//Main render loop
	while(!glfwWindowShouldClose(window)) {
		auto start = std::chrono::system_clock::now();
		scene->displayScene();
		glfwSwapBuffers(window);
		glfwPollEvents();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsed_seconds = end-start;
		float seconds = elapsed_seconds.count();
		scene->updateFrame(seconds);
	}

}

void Program::setupWindow() {
	//Initialize the GLFW windowing system
	if (!glfwInit()) {
		std::cout << "ERROR: GLFW failed to initialize, TERMINATING" << std::endl;
		return;
	}

	//Set the custom error callback function
	//Errors will be printed to the console
	glfwSetErrorCallback(ErrorCallback);

	//Attempt to create a window with an OpenGL 4.1 core profile context
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	int width = 1024;
	int height = 1024;
	window = glfwCreateWindow(width, height, "CPSC 453 OpenGL Boilerplate", 0, 0);
	if (!window) {
		std::cout << "Program failed to create GLFW window, TERMINATING" << std::endl;
		glfwTerminate();
		return;
	}

	//way to set information from key callback
	glfwSetWindowUserPointer(window, this);
	
	//Set the custom function that tracks key presses
	glfwSetKeyCallback(window, KeyCallback);

	//Bring the new window to the foreground (not strictly necessary but convenient)
	glfwMakeContextCurrent(window);

	//Intialize GLAD (finds appropriate OpenGL configuration for your system)
	if (!gladLoadGL()) {
		std::cout << "GLAD init failed" << std::endl;
		return;
	}

	//Query and print out information about our OpenGL environment
	QueryGLVersion();
}



void Program::QueryGLVersion() {
	// query opengl version and renderer information
	std::string version = reinterpret_cast<const char *>(glGetString(GL_VERSION));
	std::string glslver = reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION));
	std::string renderer = reinterpret_cast<const char *>(glGetString(GL_RENDERER));

	std::cout << "OpenGL [ " << version << " ] "
		<< "with GLSL [ " << glslver << " ] "
		<< "on renderer [ " << renderer << " ]" << std::endl;
}

void ErrorCallback(int error, const char* description) {
	std::cout << "GLFW ERROR " << error << ":" << std::endl;
	std::cout << description << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		Program* program = (Program*)glfwGetWindowUserPointer(window);
		Scene* scene = program->getScene();
		switch(key) {
			// Change scenes
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(window, GL_TRUE);
				std::cout << "Exiting program." << std::endl;
				break;

			case GLFW_KEY_1:
			{
				partNumber = 1;
				program->renderingEngine->curveType = 0;
				scene->changeTo(1);
				break;
			}
			case GLFW_KEY_2:
			{
				partNumber = 2;
				program->renderingEngine->curveType = 1;
				scene->changeTo(2);
				break;
			}
			case GLFW_KEY_3:
			{
				partNumber = 3;
				scene->changeTo(3);
				break;
			}
			case GLFW_KEY_4:
			{
				partNumber = 4;
				scene->changeTo(4);
				break;
			}
			case GLFW_KEY_RIGHT:
			{
				if (partNumber == 3 || partNumber == 4) {
					scene->nextFont();
				}
				break;
			}
			case GLFW_KEY_UP:
			{
				if (partNumber == 4) {
					scene->speedupScroll();
				}
				break;
			}
			case GLFW_KEY_DOWN:
			{
				if (partNumber == 4) {
					scene->slowdownScroll();
				}
				break;
			}
		}
	}
}

