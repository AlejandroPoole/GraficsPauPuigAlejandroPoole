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



typedef struct {
	Matrix44 viewProjection;
	Matrix44 modelMatrix;
	Vector3 Ia;
	Vector3 Intensity;
	Vector3 position;
	Vector3 eye;
	float u_colorT;
	float u_normalT;
	float u_specularT;
}sUniformData;


class Material
{
	

public:
	Shader* shader;
	Vector3 Kd;
	Vector3 Ks;
	Vector3 Ka;
	float shininess;
	//Vector3 materialColor;
	Texture* materialTexture[2];

	void Enable(const sUniformData &uniformData);
	void Disable();

};

typedef struct {
	Vector3 Position;
	Vector3 intensity;
}sLight;


