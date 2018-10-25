/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Geometry.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;
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

	std::vector<glm::vec3> elevateBezierCurve(MySegment s);
};

#endif /* SCENE_H_ */
