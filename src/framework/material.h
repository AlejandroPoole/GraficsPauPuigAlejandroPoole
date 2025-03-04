/*
	The Mesh contains the info about how to render a mesh and also how to parse it from a file.
*/

#pragma once

#include <vector>
#include "framework.h"
#include "camera.h"
#include "main/includes.h"
#include "shader.h"
#include "texture.h"
#include "Entity.h"

class Material
{
	Vector3 Kd;
	Vector3 Ks;
	Vector3 Ka;
	float shininess;
	Vector3 materialColor;
	Texture materialTexture;

public:
	Material() {};


	void Enable(const sUniformData& uniformData);
	void Disable();
};

struct sLight {
	Vector2 Position;
	Vector3 intensity;
};

struct sUniformData {
	Matrix44 viewProjection;
	Matrix44 modelMatrix;
	Material material;
	Vector3 Ia;
};