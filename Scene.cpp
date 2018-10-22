/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include <iostream>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GlyphExtractor.h"

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {

	//Does nothing related to openGL
	glfwWindowHint(GLFW_SAMPLES, 4);
	glPointSize(2);

	changeTo(2);
	
	GlyphExtractor g;
	g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");
	MyGlyph a = g.ExtractGlyph('a');

	for (unsigned int i = 0; i < a.contours.size(); i++) { //Given a has an outside contour for outline and inner for the "circle" inside the a
		std::cout << "Contour " << i << std::endl;
		for(unsigned int j = 0; j < a.contours[i].size(); j++) {
			std::cout << "Bezier curve " << j << std::endl; //A line will have 2 control points, quadratic will have 3, and cubic curve will have 4 control points
			for(unsigned int k = 0; k <= a.contours[i][j].degree; k++) {
				std::cout << "x " << a.contours[i][j].x[k] << std::endl;
				std::cout << "y " << a.contours[i][j].y[k] << std::endl;
				std::cout << std::endl;
			}
		}
	}

}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects);
}

void Scene::drawPoint(){
	Geometry point;

	point.drawMode = GL_POINTS;
	point.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 2.0f, -1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 0.0f, -1.0f, 1.0f));

	point.verts.push_back(glm::vec3( 0.0f, -1.0f, 1.0f));
	point.verts.push_back(glm::vec3( -2.0f, -1.0f, 1.0f));
	point.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));

	point.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 0.0f, 1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

	point.verts.push_back(glm::vec3( 1.2f, 0.5f, 1.0f));
	point.verts.push_back(glm::vec3( 2.5f, 1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 1.3f, -0.4f, 1.0f));

	point.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f)); //Green

	RenderingEngine::assignBuffers(point);

	RenderingEngine::setBufferData(point);

	objects.push_back(point);
}

void Scene::drawFirst() {

	quadraticBezier.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 2.0f, -1.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 0.0f, -1.0f, 1.0f));

	quadraticBezier.verts.push_back(glm::vec3( 0.0f, -1.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( -2.0f, -1.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));

	quadraticBezier.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 0.0f, 1.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

	quadraticBezier.verts.push_back(glm::vec3( 1.2f, 0.5f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 2.5f, 1.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 1.3f, -0.4f, 1.0f));

	for(int i = 0; i < quadraticBezier.verts.size(); i++)
	{
		quadraticBezier.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f)); //Blue
		quadraticBezier.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f)); //Red
		quadraticBezier.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f)); //Green
	}

	quadraticBezier.drawMode = GL_PATCHES; //If you want to use tesselation shader (for any parametric curve basically)

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(quadraticBezier);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(quadraticBezier);

	//Add the triangle to the scene objects
	objects.push_back(quadraticBezier);
}

void Scene::drawSecond() {

	quadraticBezier.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));

	quadraticBezier.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));

	quadraticBezier.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));

	quadraticBezier.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));

	quadraticBezier.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));

	for(int i = 0; i < quadraticBezier.verts.size(); i++)
	{
		quadraticBezier.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f)); //Blue
		//quadraticBezier.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f)); //Red
		//quadraticBezier.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f)); //Green
	}

	quadraticBezier.drawMode = GL_PATCHES; //If you want to use tesselation shader (for any parametric curve basically)

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(quadraticBezier);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(quadraticBezier);

	//Add the triangle to the scene objects
	objects.push_back(quadraticBezier);
}

/**
 * Change the currently selected scene. This clears the screen and draws
 * the selected scene of the most recently selected iteration if valid.
 */
void Scene::changeTo(int scene) {
	objects.clear();

	// Change to new scene
	sceneType = scene;
	std::string sceneName;
	switch(scene) {
		case 1:
			drawFirst();
			sceneName = "Part 1: Quadratic Bezier";
			break;

		case 2:
			drawSecond();
			sceneName = "Part 2: Cubic Bezier";
			break;
	}

	std::cout << "Changed to " + sceneName + " scene." << std::endl;
}

