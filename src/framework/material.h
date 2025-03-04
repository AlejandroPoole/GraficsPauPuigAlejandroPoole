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

class Material: public Entity
{
	Vector3 diffuse;
	Vector3 specular;
	Vector3 ambient;
	int shininess;

public:
	Material() {};


	void Enable();

};
