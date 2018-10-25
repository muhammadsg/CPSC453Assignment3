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

void Scene::drawScene() {
	quadraticBezier.verts.clear();
	quadraticBezier.colors.clear();

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

	cubicBezier.verts.clear();
	cubicBezier.colors.clear();
		
	cubicBezier.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));

	cubicBezier.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));

	cubicBezier.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));

	cubicBezier.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));

	cubicBezier.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
	cubicBezier.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));

	for(int i = 0; i < cubicBezier.verts.size(); i++)
	{
		cubicBezier.colors.push_back(glm::vec3( 0.0f, 0.0f, 1.0f)); //Blue
	}

	cubicBezier.drawMode = GL_PATCHES; //If you want to use tesselation shader (for any parametric curve basically)

	//Construct vao and vbos for the triangle
	RenderingEngine::assignBuffers(cubicBezier);

	//Send the triangle data to the GPU
	//Must be done every time the triangle is modified in any way, ex. verts, colors, normals, uvs, etc.
	RenderingEngine::setBufferData(cubicBezier);
}
void Scene::drawFirst() {
	//Add the quadratic to the scene objects
	objects.push_back(quadraticBezier);
}

void Scene::drawSecond() {
	//Add the cubic to the scene objects
	objects.push_back(cubicBezier);
}

void Scene::drawName() {
	GlyphExtractor g;
	g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");
	const std::string name1 = "Mohammad";
	const std::string name2 = "Tony";

	float gap = 5.0f;
	float curX = 0.0f;
	for (char c : name2) {
		MyGlyph glyph = g.ExtractGlyph(c);
		for (unsigned int i = 0; i < glyph.contours.size(); i++) {
			for(unsigned int j = 0; j < glyph.contours[i].size(); j++) {
				Geometry letter;
				letter.drawMode = GL_PATCHES;
				letter.verts = elevateBezierCurve(glyph.contours[i][j]);
				for (int i = 0; i < letter.verts.size(); i++) {
					letter.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				}
				for (glm::vec3& v : letter.verts) {
					v.x += curX;
					std::cout << v.x << ' ' << v.y << std::endl;
				}
				RenderingEngine::assignBuffers(letter);
				RenderingEngine::setBufferData(letter);
				objects.push_back(letter);
			}
		}
		curX += 0.3f;
	}
}

std::vector<glm::vec3> Scene::elevateBezierCurve(MySegment s) {
	const int MAX_DEG = 3;
	std::vector<glm::vec3> ret;
	int d = s.degree;
	for (int i = 0; i <= d; i++) {
		ret.push_back(glm::vec3(s.x[i], s.y[i], 0.0f));
	}
	while (d < MAX_DEG) {
		d++;
		std::vector<glm::vec3> tmp;
		tmp.push_back(ret[0]);
		for (int i = 1; i < ret.size(); i++) {
			glm::vec3 v = glm::mix(ret[i-1], ret[i], 1.0f - float(i)/float(d));
			tmp.push_back(v);
		}
		tmp.push_back(ret[1]);
		ret = tmp;
	}
	return ret;
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
		case 3:
			drawName();
			sceneName = "Part 3: Drawing name";
			break;
	}

	std::cout << "Changed to " + sceneName + " scene." << std::endl;
}

