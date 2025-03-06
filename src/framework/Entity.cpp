#include "Entity.h"
#include "shader.h"


//Render LAB5
void Entity::Render(sUniformData uniformData) {
	uniformData.modelMatrix = model;
	entityMaterial.Enable(uniformData);
	mesh->Render();
	entityMaterial.Disable();
}

//Render Lab4
void Entity::Render(Camera* camera) {
	meshShader->SetMatrix44("u_model", model);
	meshShader->SetMatrix44("u_viewprojection", camera->viewprojection_matrix);
	meshShader->SetTexture("u_texture", texture2);
	mesh->Render();
}

void Entity::Render(Image* framebuffer, Camera* camera, FloatImage* zBuffer,bool zbufferOn, bool InterpolatedUV, const Color &c) {
	const std::vector<Vector3> myVertices = mesh->GetVertices();
	const std::vector<Vector2> UVs = mesh->GetUVs();
	bool negZ = false;
	for (int i = 0; i < myVertices.size()-2;i+=3) { //For per iterar els triangles
		Vector3 P0 = myVertices.at(i);
		Vector3 P1= myVertices.at(i+1);
		Vector3 P2= myVertices.at(i+2);
		
		//local to world
		P0 = model * P0;
		P1 = model * P1;
		P2 = model * P2;
		
		//word to clip thanks to viewing and proojection transformation
		P0 = camera->ProjectVector(P0, negZ);
		P1 = camera->ProjectVector(P1, negZ);
		P2 = camera->ProjectVector(P2, negZ);

		Vector2 uv0 = UVs.at(i);
		Vector2 uv1 = UVs.at(i+1);
		Vector2 uv2 = UVs.at(i+2);
		//Clip to Framebuffer Space
		
		//Dins el cub 
		if (P0.x >= -1 && P0.x <= 1 && P0.y >= -1 && P0.y <= 1 && P0.z <= 1 && P0.z >= -1 && P1.z <= 1 &&
			P1.x >= -1 && P1.x <= 1 && P1.y >= -1 && P1.y <= 1 && P1.z >= -1 && P2.z >= -1 && P2.z <= 1 &&
			P2.x >= -1 && P2.x <= 1 && P2.y >= -1 && P2.y <= 1 ){
			
			//Transform to framebuffer space
			P0.x = (P0.x + 1) * (framebuffer->width / 2);
			P0.y = (P0.y + 1) * (framebuffer->height / 2);
			P1.x = (P1.x + 1) * (framebuffer->width / 2);
			P1.y = (P1.y + 1) * (framebuffer->height / 2);
			P2.x = (P2.x + 1) * (framebuffer->width / 2);
			P2.y = (P2.y + 1) * (framebuffer->height / 2);
			Vector3 P0_2D = { P0.x, P0.y, P0.z};
			Vector3 P1_2D = { P1.x, P1.y, P1.z};
			Vector3 P2_2D = { P2.x, P2.y, P2.z};
			//Draw Triangle

			

			
			
			if (!textureOn) {
				texture = NULL;
			}
			else if (textureOn) {
				texture = n;
			}

			if (zbufferOn) {
				zBuffer = NULL;
			}
			else {
				zBuffer = zbufferTemp;
			}

			if (InterpolatedUV) {
				framebuffer->DrawTriangleInterpolated(P0_2D, P1_2D, P2_2D, Color::GREEN, Color::RED, Color::BLUE, zBuffer, texture, uv0, uv1, uv2);
				
			}
			else if (!InterpolatedUV) {
				framebuffer->DrawTriangle({ P0_2D.x, P0_2D.y }, { P1_2D.x, P1_2D.y }, { P2_2D.x, P2_2D.y }, c, true, c); 

			}
			

			
		}
		
	}
}


void Entity::Update(float seconds_elapsed) {
	if (Scale<50) {

		model._11 += 0.01;
		model._22 += 0.01;
		model._33 += 0.01;
		Scale += 1;
	}
	else if (Scale>=50 && Scale<100){
		model._11 -= 0.01;
		model._22 -= 0.01;
		model._33 -= 0.01;
		Scale +=1;
	}
	else {
		Scale = 0;
	}
}

void Entity::Update2(float seconds_elapsed) {

	if (goUp<50) {
		model.Translate(0, 0.01, 0);
		goUp += 1;
	}
	else if(goUp>=50 && goUp<100) {
		model.Translate(0, -0.01, 0);
		goUp +=1;
	}
	else {
		goUp = 0;
	}
}

void Entity::Update3(float seconds_elapsed) {
	model.Translate(-0.5, 0, 0);
	model.Rotate(PI / 15, { 0,1,0 });
	model.Translate(0.5, 0, 0);
}