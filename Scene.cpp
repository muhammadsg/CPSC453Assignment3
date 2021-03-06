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


Scene::Scene(RenderingEngine* renderer) :
	renderer(renderer), pixelsPerSec(3), scrolling(false), partNumber(0) {
	glfwWindowHint(GLFW_SAMPLES, 4);
	glPointSize(8);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	renderer->RenderScene(objects, polygonExtra, point);
	if (!lines.empty()) renderer->RenderLine(lines);
	if (!quadratics.empty()) renderer->RenderQuadratic(quadratics);
	if (!cubics.empty()) renderer->RenderCubic(cubics);
}

void Scene::drawPoint1() {
	RenderingEngine::deleteBufferData(point);
	point.verts.clear();
	point.colors.clear();

	point.verts.push_back(glm::vec3( 2.0f, -1.0f, 1.0f));
	point.verts.push_back(glm::vec3( -2.0f, -1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 2.5f, 1.0f, 1.0f));

	for(int i = 0; i < point.verts.size(); i++)
	{
		point.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f)); //Green for off curve control points
	}
	point.drawMode = GL_POINTS;

	point.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 0.0f, -1.0f, 1.0f));

	point.verts.push_back(glm::vec3( 0.0f, -1.0f, 1.0f));
	point.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));

	point.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

	point.verts.push_back(glm::vec3( 1.2f, 0.5f, 1.0f));
	point.verts.push_back(glm::vec3( 1.3f, -0.4f, 1.0f));
	point.verts.push_back(glm::vec3( 0.0f, 1.0f, 1.0f));

	const float scaling = 0.35f;
	for (glm::vec3& v : point.verts) {
		v *= scaling;
	}

	for(int i = 3; i < point.verts.size(); i++)
	{
		point.colors.push_back(glm::vec3( 0.5f, 0.1f, 0.9f)); //Purple for on curve control points
	}
	point.drawMode = GL_POINTS;

	RenderingEngine::assignBuffers(point);
	RenderingEngine::setBufferData(point);
}

void Scene::drawPoint2() {

	point.verts.clear();
	point.colors.clear();

	point.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
	point.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
	
	point.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
	point.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));

	point.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
	point.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
	
	point.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
	point.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
	
	point.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
	point.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));

	for(int i = 0; i < point.verts.size(); i++)
	{
		point.colors.push_back(glm::vec3( 0.0f, 1.0f, 0.0f)); //Green
	}
	point.drawMode = GL_POINTS;


	point.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	point.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));

	point.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
	point.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));

	point.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
	point.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));

	point.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
	point.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));

	point.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
	point.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));

	const float scaling = 0.10f;
	for (glm::vec3& v : point.verts) {
		v *= scaling;
		v.x -= 0.4f;
		v.y -= 0.1f;
	}

	for(int i = 10; i < point.verts.size(); i++)
	{
		point.colors.push_back(glm::vec3( 0.5f, 0.1f, 0.9f)); //Purple for on curve control points
	}
	point.drawMode = GL_POINTS;

	RenderingEngine::assignBuffers(point);
	RenderingEngine::setBufferData(point);

}

void Scene::drawPolygon1() {

	polygonExtra.clear();

	Geometry p1;

	p1.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	p1.verts.push_back(glm::vec3( 2.0f, -1.0f, 1.0f));
	p1.verts.push_back(glm::vec3( 0.0f, -1.0f, 1.0f));

	p1.verts.push_back(glm::vec3( 0.0f, -1.0f, 1.0f));
	p1.verts.push_back(glm::vec3( -2.0f, -1.0f, 1.0f));
	p1.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));

	p1.verts.push_back(glm::vec3( -1.0f, 1.0f, 1.0f));
	p1.verts.push_back(glm::vec3( 0.0f, 1.0f, 1.0f));
	p1.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));

	const float scaling = 0.35f;
	for (glm::vec3& v : p1.verts) {
		v *= scaling;
	}

	for(int i = 0; i < p1.verts.size(); i++)
	{
		p1.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f)); //Red
	}
	p1.drawMode = GL_LINE_STRIP;

	RenderingEngine::assignBuffers(p1);
	RenderingEngine::setBufferData(p1);

	polygonExtra.push_back(p1);

	Geometry polygon2;

	polygon2.verts.push_back(glm::vec3( 1.2f, 0.5f, 1.0f));
	polygon2.verts.push_back(glm::vec3( 2.5f, 1.0f, 1.0f));
	polygon2.verts.push_back(glm::vec3( 1.3f, -0.4f, 1.0f));


	for (glm::vec3& v : polygon2.verts) {
		v *= scaling;
	}

	for(int i = 0; i < polygon2.verts.size(); i++)
	{
		polygon2.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f)); //Red
	}
	polygon2.drawMode = GL_LINE_STRIP;

	RenderingEngine::assignBuffers(polygon2);
	RenderingEngine::setBufferData(polygon2);

	polygonExtra.push_back(polygon2);
}

void Scene::drawPolygon2() {

	polygonExtra.clear();

	Geometry p0;
	p0.verts.push_back(glm::vec3( 1.0f, 1.0f, 1.0f));
	p0.verts.push_back(glm::vec3( 4.0f, 0.0f, 1.0f));
	p0.verts.push_back(glm::vec3( 6.0f, 2.0f, 1.0f));
	p0.verts.push_back(glm::vec3( 9.0f, 1.0f, 1.0f));

	const float scaling = 0.10f;
	for (glm::vec3& v : p0.verts) {
		v *= scaling;
		v.x -= 0.4f;
		v.y -= 0.1f;
	}

	for(int i = 0; i < p0.verts.size(); i++)
	{
		p0.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f)); //Red
	}

	p0.drawMode = GL_LINE_STRIP;

	RenderingEngine::assignBuffers(p0);
	RenderingEngine::setBufferData(p0);

	Geometry p1;

	p1.verts.push_back(glm::vec3( 8.0f, 2.0f, 1.0f));
	p1.verts.push_back(glm::vec3( 0.0f, 8.0f, 1.0f));
	p1.verts.push_back(glm::vec3( 0.0f, -2.0f, 1.0f));
	p1.verts.push_back(glm::vec3( 8.0f, 4.0f, 1.0f));

	for (glm::vec3& v : p1.verts) {
		v *= scaling;
		v.x -= 0.4f;
		v.y -= 0.1f;
	}

	for(int i = 0; i < p1.verts.size(); i++)
	{
		p1.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f)); //Red
	}

	p1.drawMode = GL_LINE_STRIP;

	RenderingEngine::assignBuffers(p1);
	RenderingEngine::setBufferData(p1);

	Geometry p2;

	p2.verts.push_back(glm::vec3( 5.0f, 3.0f, 1.0f));
	p2.verts.push_back(glm::vec3( 3.0f, 2.0f, 1.0f));
	p2.verts.push_back(glm::vec3( 3.0f, 3.0f, 1.0f));
	p2.verts.push_back(glm::vec3( 5.0f, 2.0f, 1.0f));

	for (glm::vec3& v : p2.verts) {
		v *= scaling;
		v.x -= 0.4f;
		v.y -= 0.1f;
	}

	for(int i = 0; i < p2.verts.size(); i++)
	{
		p2.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f)); //Red
	}

	p2.drawMode = GL_LINE_STRIP;

	RenderingEngine::assignBuffers(p2);
	RenderingEngine::setBufferData(p2);

	Geometry p3;

	p3.drawMode = GL_LINE_STRIP;

	p3.verts.push_back(glm::vec3( 3.0f, 2.2f, 1.0f));
	p3.verts.push_back(glm::vec3( 3.5f, 2.7f, 1.0f));
	p3.verts.push_back(glm::vec3( 3.5f, 3.3f, 1.0f));
	p3.verts.push_back(glm::vec3( 3.0f, 3.8f, 1.0f));

	for (glm::vec3& v : p3.verts) {
		v *= scaling;
		v.x -= 0.4f;
		v.y -= 0.1f;
	}

	for(int i = 0; i < p3.verts.size(); i++)
	{
		p3.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f)); //Red
	}

	RenderingEngine::assignBuffers(p3);
	RenderingEngine::setBufferData(p3);

	Geometry p4;
	p4.drawMode = GL_LINE_STRIP;

	p4.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));
	p4.verts.push_back(glm::vec3( 2.4f, 3.8f, 1.0f));
	p4.verts.push_back(glm::vec3( 2.4f, 3.2f, 1.0f));
	p4.verts.push_back(glm::vec3( 2.8f, 3.5f, 1.0f));

	for (glm::vec3& v : p4.verts) {
		v *= scaling;
		v.x -= 0.4f;
		v.y -= 0.1f;
	}

	for(int i = 0; i < p4.verts.size(); i++)
	{
		p4.colors.push_back(glm::vec3( 1.0f, 0.0f, 0.0f)); //Red
	}

	RenderingEngine::assignBuffers(p4);
	RenderingEngine::setBufferData(p4);

	polygonExtra = { p0, p1, p2, p3, p4 };
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

	float scaling = 0.35f;
	for (glm::vec3& v : quadraticBezier.verts) {
		v *= scaling;
	}

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

	scaling = 0.10f;
	for (glm::vec3& v : cubicBezier.verts) {
		v *= scaling;
		v.x -= 0.4f;
		v.y -= 0.1f;
	}

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
	const float scaling = 0.50f;
	const std::string text = "The quick brown fox jumps over the lazy dog. ";
	float curX = 1.0f;
	for (char c : text) {
		MyGlyph glyph = glyphExtractor.ExtractGlyph(c);
		glyphs.push_back({curX, glyph});
		curX += scaling * glyph.advance;
	}
}

void Scene::updateFrame(float secs) {
	if (glyphs.empty() || !scrolling) {
		return;
	}
	const float scaling = 0.50f;
	float endX = 0.0f;
	for (auto& glyphPair : glyphs) {
		glyphPair.first -= secs * pixelsPerSec;
		endX = std::max(endX, glyphPair.first + scaling * glyphPair.second.advance);
	}
	if (glyphs[0].first + glyphs[0].second.advance < -1.1f) {
		glyphs[0].first = endX;
		std::sort(glyphs.begin(), glyphs.end(),
			[](std::pair<float, MyGlyph>& a, std::pair<float, MyGlyph>& b) {
			return a.first < b.first;
		});
	}

	deleteGeometries(lines);
	deleteGeometries(quadratics);
	deleteGeometries(cubics);
	float curX = glyphs[0].first;
	for (auto glyphPair : glyphs) {
		MyGlyph g = glyphPair.second;
		for (unsigned int i = 0; i < g.contours.size(); i++) {
			for(MySegment s : g.contours[i]) {
				Geometry letter;
				for (int k = 0; k <= s.degree; k++) {
					glm::vec3 v = scaling * glm::vec3(s.x[k], s.y[k], 0.0f);
					v.x += curX;
					letter.verts.push_back(v);
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
		curX += g.advance * scaling;
	}
}

void Scene::deleteGeometries(std::vector<Geometry>& geometry) {
	for (Geometry g : geometry) {
		RenderingEngine::deleteBufferData(g);
	}
	geometry.clear();
}

void Scene::drawName() {
	lines.clear();
	quadratics.clear();
	cubics.clear();
	glyphs.clear();
	const std::string name1 = "Muhammad";
	const std::string name2 = "Tony";

	float curX = -1.0f;
	const float scaling = 0.35f;
	for (char c : name1) {
		MyGlyph glyph = glyphExtractor.ExtractGlyph(c);
		for (unsigned int i = 0; i < glyph.contours.size(); i++) {
			for(MySegment s : glyph.contours[i]) {
				Geometry letter;
				for (int k = 0; k <= s.degree; k++) {
					glm::vec3 v = scaling * glm::vec3(s.x[k], s.y[k], 0.0f);
					v.x += curX;
					v.y += 0.25f;
					letter.verts.push_back(v);
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
		curX += glyph.advance * scaling;
	}

	curX = -1.0f;
	for (char c : name2) {
		MyGlyph glyph = glyphExtractor.ExtractGlyph(c);
		for (unsigned int i = 0; i < glyph.contours.size(); i++) {
			for(MySegment s : glyph.contours[i]) {
				Geometry letter;
				for (int k = 0; k <= s.degree; k++) {
					glm::vec3 v = scaling * glm::vec3(s.x[k], s.y[k], 0.0f);
					v.x += curX;
					v.y -= 0.25f;
					letter.verts.push_back(v);
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
		curX += glyph.advance * scaling;
	}
}

/**
 * Change the currently selected scene. This clears the screen and draws
 * the selected scene of the most recently selected iteration if valid.
 */
void Scene::changeTo(int scene) {
	objects.clear();
	lines.clear();
	quadratics.clear();
	cubics.clear();
	glyphs.clear();

	// Change to new scene
	sceneType = scene;
	std::string sceneName;
	std::string fontFile;
	switch(scene) {
		case 1:
			drawFirst();
			drawPoint1();
			drawPolygon1();
			sceneName = "Part 1: Quadratic Bezier with control points and polygons";
			scrolling = false;
			break;
		case 2:
			drawSecond();
			drawPoint2();
			drawPolygon2();
			sceneName = "Part 2: Cubic Bezier";
			scrolling = false;
			break;
		case 3:
			partNumber = 3;
			fontFile = part2Fonts[p2fid];
			glyphExtractor.LoadFontFile(fontFile);
			drawName();
			sceneName = "Part 3: Drawing name";
			scrolling = false;
			break;
		case 4:
			partNumber = 4;
			fontFile = part3Fonts[p3fid];
			glyphExtractor.LoadFontFile(fontFile);
			drawScrollingText();
			sceneName = "Part 4: Drawing scrolling text";
			scrolling = true;
			break;
	}

	std::cout << "Changed to " + sceneName + " scene." << std::endl;
}

void Scene::nextFont() {
	if (partNumber == 3) {
		p2fid = (p2fid + 1) % 3;
		std::string fontFile = part2Fonts[p2fid];
		glyphExtractor.LoadFontFile(fontFile);
		drawName();
	} else if (partNumber == 4) {
		p3fid = (p3fid + 1) % 3;
		std::string fontFile = part3Fonts[p3fid];
		glyphExtractor.LoadFontFile(fontFile);
		drawScrollingText();
	}
}

void Scene::speedupScroll() {
	if (pixelsPerSec < 6.0f) pixelsPerSec += 0.5f;
}

void Scene::slowdownScroll() {
	if (pixelsPerSec > 1.0f) pixelsPerSec -= 0.5f;
}
