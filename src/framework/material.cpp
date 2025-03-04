#include "mesh.h"
#include "utils.h"
#include "camera.h"
#include "material.h"
#include "shader.h"
#include "texture.h"

#include <string>
#include <sys/stat.h>
#include <cstring>

void Material::Enable(const sUniformData &uniformData){
	ka = { 0.1, 0.1, 0.1 };
	kd = { 0.6, 0.6, 0.6 };
	ks = { 0.3, 0.3, 0.3 };
	shininess = 100;
}

void Material::Disable(){
	ambient = { 0,0,0};
	diffuse = { 0,0,0};
	specular = { 0,0,0};
	shininess = 0;
}
