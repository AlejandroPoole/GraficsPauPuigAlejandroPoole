/*
	The Mesh contains the info about how to render a mesh and also how to parse it from a file.
*/

#pragma once
#include "mesh.h"
#include "image.h"

class Entity {
public:
	Mesh* mesh;
	Matrix44 model;

	Entity() {};
	Entity(Matrix44 _model, Mesh* _mymesh) { mesh = _mymesh;model = _model; };

	void Render(Image* framebuffer, Camera* camera, const Color& c);

	int b;
};