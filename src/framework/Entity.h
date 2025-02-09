/*
	The Mesh contains the info about how to render a mesh and also how to parse it from a file.
*/

#pragma once
#include "mesh.h"
#include "image.h"


class Entity {


public:
	int goUp = 0;
	int Scale = 0;
	Mesh* mesh;
	Matrix44 model;

	Entity() {};
	Entity(Matrix44 _model, Mesh* _mymesh) { mesh = _mymesh;model = _model; };

	void Render(Image* framebuffer, Camera* camera, const Color& c);
	void Update(float seconds_elapsed);
	void Update2(float seconds_elapsed);
	void Update3(float seconds_elapsed);
};