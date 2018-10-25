/*
 * Scene.cpp
 *
 *  Created on: Sep 10, 2018
 *  Author: John Hall
 */

#include "Scene.h"

#include <iostream>
#include <algorithm>

#include "RenderingEngine.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//**Must include glad and GLFW in this order or it breaks**
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GlyphExtractor.h"


Scene::Scene(RenderingEngine* renderer) : renderer(renderer), pixelsPerSec(10) {

	//Does nothing related to openGL

	glfwWindowHint(GLFW_SAMPLES, 4);
	glPointSize(2);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	// renderer->RenderScene(objects);
	if (!lines.empty()) renderer->RenderLine(lines);
	if (!quadratics.empty()) renderer->RenderQuadratic(quadratics);
	if (!cubics.empty()) renderer->RenderCubic(cubics);
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

void Scene::drawScrollingText() {
	lines.clear();
	quadratics.clear();
	cubics.clear();
	glyphs.clear();
	GlyphExtractor g;
	g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");

	const std::string text = "The quick brown fox jumps over the lazy dog.";
	float curX = 1.0f;
	for (char c : text) {
		MyGlyph glyph = g.ExtractGlyph(c);
		glyphs.push_back({curX, glyph});
		curX += glyph.advance;
	}
}

void Scene::updateFrame(float secs) {
	if (glyphs.empty()) {
		return;
	}
	float endX = 0.0f;
	for (auto& glyphPair : glyphs) {
		glyphPair.first -= secs * pixelsPerSec;
		endX = std::max(endX, glyphPair.first + glyphPair.second.advance);
	}
	if (glyphs[0].first + glyphs[0].second.advance < -1.1f) {
		glyphs[0].first = endX;
	}
	std::sort(glyphs.begin(), glyphs.end(),
		[](std::pair<float, MyGlyph>& a, std::pair<float, MyGlyph>& b) {
		return a.first < b.first;
	});

	lines.clear();
	quadratics.clear();
	cubics.clear();
	float curX = glyphs[0].first;
	for (auto glyphPair : glyphs) {
		MyGlyph g = glyphPair.second;
		for (unsigned int i = 0; i < g.contours.size(); i++) {
			for(MySegment s : g.contours[i]) {
				Geometry letter;
				for (int k = 0; k <= s.degree; k++) {
					letter.verts.push_back(glm::vec3(curX + s.x[k], s.y[k], 0.0f));
					letter.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				}
				RenderingEngine::assignBuffers(letter);
				RenderingEngine::setBufferData(letter);
				if (s.degree == 1) {
					letter.drawMode = GL_LINES;
					lines.push_back(letter);
				} else if (s.degree == 2) {
					letter.drawMode = GL_PATCHES;
					quadratics.push_back(letter);
				} else {
					letter.drawMode = GL_PATCHES;
					cubics.push_back(letter);
				}
			}
		}
		curX += g.advance;
	}
}

void Scene::drawName() {
	lines.clear();
	quadratics.clear();
	cubics.clear();

	GlyphExtractor g;
	g.LoadFontFile("fonts/alex-brush/AlexBrush-Regular.ttf");
	const std::string name1 = "Mohammad";
	const std::string name2 = "Tony";

	float curX = -1.0f;
	for (char c : name2) {
		MyGlyph glyph = g.ExtractGlyph(c);
		for (unsigned int i = 0; i < glyph.contours.size(); i++) {
			for(MySegment s : glyph.contours[i]) {
				Geometry letter;
				for (int k = 0; k <= s.degree; k++) {
					letter.verts.push_back(glm::vec3(curX + s.x[k], s.y[k], 0.0f));
					letter.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				}
				RenderingEngine::assignBuffers(letter);
				RenderingEngine::setBufferData(letter);
				if (s.degree == 1) {
					letter.drawMode = GL_LINES;
					lines.push_back(letter);
				} else if (s.degree == 2) {
					letter.drawMode = GL_PATCHES;
					quadratics.push_back(letter);
				} else {
					letter.drawMode = GL_PATCHES;
					cubics.push_back(letter);
				}
			}
		}
		std::cout << glyph.advance << std::endl;
		curX += glyph.advance;
	}
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
		case 4:
			drawScrollingText();
			sceneName = "Part 4: Drawing scrolling text";
			break;
	}

	std::cout << "Changed to " + sceneName + " scene." << std::endl;
}

