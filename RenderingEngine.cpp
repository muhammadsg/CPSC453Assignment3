/*
 * RenderingEngine.cpp
 *
 *  Created on: Sep 10, 2018
 *      Author: John Hall
 */

#include "RenderingEngine.h"

#include <iostream>

//cpp file purposely included here because it just contains some global functions
#include "ShaderTools.h"

RenderingEngine::RenderingEngine() {
	shaderProgram = ShaderTools::InitializeShaders(0);
	shaderProgram2 = ShaderTools::InitializeShaders(1);
	lineShaderProgram = ShaderTools::InitializeShaders(2);
	if (lineShaderProgram == 0 || shaderProgram == 0 || shaderProgram2 == 0) {
		std::cout << "Program could not initialize shaders, TERMINATING" << std::endl;
		return;
	}
}

RenderingEngine::~RenderingEngine() {

}

void RenderingEngine::RenderScene(const std::vector<Geometry>& objects, const std::vector<Geometry>& polygonExtra, Geometry point) {
	//Clears the screen to a dark grey background
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// bind our shader program and the vertex array object containing our
	// scene geometry, then tell OpenGL to draw our geometry
	glUseProgram(lineShaderProgram);
	
	if (!polygonExtra.empty()) {
		for (const Geometry& p : polygonExtra) {
			glBindVertexArray(p.vao);
			glDrawArrays(p.drawMode, 0, p.verts.size());
			glBindVertexArray(0);
		}
	}

	if (!point.verts.empty()) {
		glBindVertexArray(point.vao);
		glDrawArrays(point.drawMode, 0, point.verts.size());
		glBindVertexArray(0);
	}

	if (curveType == 0)
	{
		glUseProgram(shaderProgram);
		glPatchParameteri(GL_PATCH_VERTICES, 3); //Says, for vertices passed in; every 3 vertices should be interpreted as a patch (3 for quadratic, 4 for cubic)
		GLuint location = glGetUniformLocation(shaderProgram, "curveType");
		glUniform1i(location, curveType);
	}

	if (curveType == 1)
	{
		glUseProgram(shaderProgram2);
		glPatchParameteri(GL_PATCH_VERTICES, 4); //Says, for vertices passed in; every 3 vertices should be interpreted as a patch (3 for quadratic, 4 for cubic)
		GLuint location = glGetUniformLocation(shaderProgram2, "curveType");
		glUniform1i(location, curveType);
	}

	if (!objects.empty()) {
		for (const Geometry& g : objects) {
			glBindVertexArray(g.vao);
			glDrawArrays(g.drawMode, 0, g.verts.size());
			glBindVertexArray(0);
		}
	}
	glUseProgram(0);

	// check for an report any OpenGL errors
	CheckGLErrors();
}

void RenderingEngine::RenderLine(std::vector<Geometry>& objects) {
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	//Clears the screen to a dark grey background
	glUseProgram(lineShaderProgram);

	for (Geometry& g : objects) {
		glBindVertexArray(g.vao);
		glDrawArrays(g.drawMode, 0, g.verts.size());
		glBindVertexArray(0);
	}

	glUseProgram(0);
	CheckGLErrors();
}

void RenderingEngine::RenderQuadratic(std::vector<Geometry>& objects) {
	glUseProgram(shaderProgram);
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	GLuint location = glGetUniformLocation(shaderProgram, "curveType");
	glUniform1i(location, /*curveType=*/0);

	for (Geometry& g : objects) {
		glBindVertexArray(g.vao);
		glDrawArrays(g.drawMode, 0, g.verts.size());
		glBindVertexArray(0);
	}

	glUseProgram(0);
	CheckGLErrors();
}

void RenderingEngine::RenderCubic(std::vector<Geometry>& objects) {
	glUseProgram(shaderProgram2);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	GLuint location = glGetUniformLocation(shaderProgram2, "curveType");
	glUniform1i(location, /*curveType=*/1);

	for (Geometry& g : objects) {
		glBindVertexArray(g.vao);
		glDrawArrays(g.drawMode, 0, g.verts.size());
		glBindVertexArray(0);
	}

	glUseProgram(0);
	CheckGLErrors();
}

void RenderingEngine::assignBuffers(Geometry& geometry) {
	//Generate vao for the object
	//Constant 1 means 1 vao is being generated
	glGenVertexArrays(1, &geometry.vao);
	glBindVertexArray(geometry.vao);

	//Generate vbos for the object
	//Constant 1 means 1 vbo is being generated
	glGenBuffers(1, &geometry.vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.vertexBuffer);
	//Parameters in order: Index of vbo in the vao, number of primitives per element, primitive type, etc.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	/*glGenBuffers(1, &geometry.normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(2);*/

	glGenBuffers(1, &geometry.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.colorBuffer);
	//Parameters in order: Index of vbo in the vao, number of primitives per element, primitive type, etc.
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);

	/*glGenBuffers(1, &geometry.uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, geometry.uvBuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(1);*/
}

void RenderingEngine::setBufferData(Geometry& geometry) {
	//Send geometry to the GPU
	//Must be called whenever anything is updated about the object
	glBindBuffer(GL_ARRAY_BUFFER, geometry.vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry.verts.size(), geometry.verts.data(), GL_STATIC_DRAW);

	/*glBindBuffer(GL_ARRAY_BUFFER, geometry.normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry.normals.size(), geometry.normals.data(), GL_STATIC_DRAW);*/

	glBindBuffer(GL_ARRAY_BUFFER, geometry.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * geometry.colors.size(), geometry.colors.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, geometry.uvBuffer);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * geometry.uvs.size(), geometry.uvs.data(), GL_STATIC_DRAW);
}

void RenderingEngine::deleteBufferData(Geometry& geometry) {
	glDeleteBuffers(1, &geometry.vertexBuffer);
	glDeleteBuffers(1, &geometry.normalBuffer);
	glDeleteBuffers(1, &geometry.colorBuffer);
	glDeleteBuffers(1, &geometry.uvBuffer);
	glDeleteVertexArrays(1, &geometry.vao);
}

bool RenderingEngine::CheckGLErrors() {
	bool error = false;
	for (GLenum flag = glGetError(); flag != GL_NO_ERROR; flag = glGetError())
	{
		std::cout << "OpenGL ERROR:  ";
		switch (flag) {
		case GL_INVALID_ENUM:
			std::cout << "GL_INVALID_ENUM" << std::endl; break;
		case GL_INVALID_VALUE:
			std::cout << "GL_INVALID_VALUE" << std::endl; break;
		case GL_INVALID_OPERATION:
			std::cout << "GL_INVALID_OPERATION" << std::endl; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION" << std::endl; break;
		case GL_OUT_OF_MEMORY:
			std::cout << "GL_OUT_OF_MEMORY" << std::endl; break;
		default:
			std::cout << "[unknown error code]" << std::endl;
		}
		error = true;
	}
	return error;
}
