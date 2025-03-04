/*
	The Mesh contains the info about how to render a mesh and also how to parse it from a file.
*/

#pragma once
#include "mesh.h"
#include "image.h"
#include "shader.h"
#include "material.h"


class Entity {


public:
	int goUp = 0;
	int Scale = 0;
	Mesh* mesh;
	Matrix44 model;
	Image* texture;
	Image* n;
	bool textureOn = false;
	FloatImage* zbufferTemp;
	Shader* meshShader;
	Texture* texture2;
	Material entityMaterial;

	Entity() {};
	Entity(Matrix44 _model, Mesh* _mymesh) { mesh = _mymesh;model = _model; };

	void Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer, bool zbufferOn, bool InterpolatedUV, const Color& c);
	void Render(sUniformData uniformData);
	void Render(Camera* camera);
	void Update(float seconds_elapsed);
	void Update2(float seconds_elapsed);
	void Update3(float seconds_elapsed);
};

