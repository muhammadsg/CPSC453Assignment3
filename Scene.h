/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>
#include <utility>

#include "Geometry.h"
#include "GlyphExtractor.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;
struct MyGlyph;
struct MySegment;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	void drawPoint();
	void drawScene();
	void drawFirst();
	void drawSecond();
	void drawName();
	void drawScrollingText();
	void updateFrame(float secs);

	void changeTo(int scene);

	//Send geometry to the renderer
	void displayScene();

	int sceneType;


private:
	RenderingEngine* renderer;

	//Geometry
	Geometry quadraticBezier;
	Geometry cubicBezier;
	Geometry letter;

	//list of objects in the scene
	std::vector<Geometry> objects;

	std::vector<Geometry> lines;
	std::vector<Geometry> quadratics;
	std::vector<Geometry> cubics;
	float pixelsPerSec;
	
	std::vector<std::pair<float, MyGlyph>> glyphs;
	bool scrolling;

	void deleteGeometries(std::vector<Geometry>& geometries);
};

#endif /* SCENE_H_ */
