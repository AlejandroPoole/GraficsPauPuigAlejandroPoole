#include "Entity.h"

void Entity::Render(Image* framebuffer, Camera* camera, const Color& c) {
	const std::vector<Vector3> myVertices = mesh->GetVertices();
	for (int i = 0; i < ? ? ? ;++i) { //For per iterar els triangles
		Vector3 P0 = myVertices.at(i);
		Vector3 P1= myVertices.at(i+1);
		Vector3 P2= myVertices.at(i+2);

		int a;

		//Project Vector

		//Clip to Framebuffer Space

		//Draw Triangle
	}
}