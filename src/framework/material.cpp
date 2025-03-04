#include "mesh.h"
#include "utils.h"
#include "camera.h"
#include "material.h"
#include "shader.h"
#include "texture.h"

#include <string>
#include <sys/stat.h>
#include <cstring>

void Material::Enable(){
	ambient = { 0.1, 0.1, 0.1 };
	diffuse = { 0.6, 0.6, 0.6 };
	specular = { 0.3, 0.3, 0.3 };
	shininess = 100;
}
