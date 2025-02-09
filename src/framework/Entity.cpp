#include "Entity.h"

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
	const std::vector<Vector3> myVertices = mesh->GetVertices();
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

		//Clip to Framebuffer Space

		//Dins el cub 
		if (P0.x >= -1 && P0.x <= 1 && P0.y >= -1 && P0.y <= 1 && 
			P1.x >= -1 && P1.x <= 1 && P1.y >= -1 && P1.y <= 1 &&
			P2.x >= -1 && P2.x <= 1 && P2.y >= -1 && P2.y <= 1 ){
			
			//Transform to framebuffer space
			P0.x = (P0.x + 1) * (framebuffer->width / 2);
			P0.y = (P0.y + 1) * (framebuffer->height / 2);
			P1.x = (P1.x + 1) * (framebuffer->width / 2);
			P1.y = (P1.y + 1) * (framebuffer->height / 2);
			P2.x = (P2.x + 1) * (framebuffer->width / 2);
			P2.y = (P2.y + 1) * (framebuffer->height / 2);
			Vector2 P0_2D = { P0.x, P0.y};
			Vector2 P1_2D = { P1.x, P1.y };
			Vector2 P2_2D = { P2.x, P2.y };
			//Draw Triangle
			
			framebuffer->DrawTriangle(P0_2D, P1_2D, P2_2D, c, false, c);
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