#include "mesh.h"
#include "utils.h"
#include "camera.h"
#include "material.h"
#include "shader.h"
#include "texture.h"

#include <string>
#include <sys/stat.h>
#include <cstring>

void Material::Enable(const sUniformData& uniformData) {
	//Material properties
	shader->Enable();
	shader->SetVector3("u_kd", Kd);
	shader->SetVector3("u_ks", Ks);
	shader->SetVector3("u_ka",Ka);
	shader->SetFloat("u_shininess", shininess);
	shader->SetMatrix44("u_model", uniformData.modelMatrix);
	shader->SetMatrix44("u_viewprojection", uniformData.viewProjection);
	shader->SetTexture("u_texture", uniformData.texture);
	shader->SetVector3("u_Ia", uniformData.Ia);
	shader->SetVector3("u_intensity", uniformData.Intensity);
	shader->SetVector3("u_position", uniformData.position);
	shader->SetVector3("u_eye", uniformData.eye);
	
	
}

void Material::Disable(){
	shader->Disable();
}
