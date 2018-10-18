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

	quadraticBezier.verts.push_back(glm::vec3( 0.0f, 0.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 1.0f,  0.0f, 1.0f));
	quadraticBezier.verts.push_back(glm::vec3( 1.0f, -1.0f, 1.0f));

	quadraticBezier.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f)); //Blue
	quadraticBezier.colors.push_back(glm::vec3( 1.0f,  0.0f, 0.0f)); //Red

	quadraticBezier.drawMode = GL_PATCHES; //If you want to use tesselation shader (for any parametric curve basically)

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(quadraticBezier);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(quadraticBezier);

	//Add the triangle to the scene objects
	objects.push_back(quadraticBezier);

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

