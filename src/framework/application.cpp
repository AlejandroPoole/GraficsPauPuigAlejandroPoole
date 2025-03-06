#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "Entity.h"
#include "material.h"

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	this->mouse_state = 0;
	this->time = 0.f;
	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(nullptr);

	this->framebuffer.Resize(w, h);
}

Application::~Application()
{
}

void Application::Init(void)
{

	quadShader = Shader::Get("../res/shaders/quad.vs", "../res/shaders/quad.fs");
	quad.CreateQuad();
	texture = Texture::Get("../res/images/fruits.png");
	

	Matrix44 mymodel4;
	Mesh* mymesh4 = new Mesh();
	mymesh4->LoadOBJ("..//res/meshes/lee.obj");
	entity[0].model = mymodel4;
	entity[0].mesh = mymesh4;
	entity[0].texture2 = Texture::Get("../res/textures/lee_color_specular.tga");
	entity[0].n = entity[0].texture;
	entity[0].zbufferTemp = &zBuffer;
	entity[0].meshShader = Shader::Get("../res/shaders/simple.vs", "../res/shaders/simple.fs");


	Matrix44 mymodel2;
	Mesh* mymesh2 = new Mesh();
	mymesh2->LoadOBJ("..//res/meshes/lee.obj");
	entity[1].model = mymodel2;
	entity[1].mesh = mymesh2;
	entity[1].entityMaterial.materialTexture = Texture::Get("../res/textures/lee_color_specular.tga");
	entity[1].entityMaterial.shader = Shader::Get("../res/shaders/gouraud.vs", "../res/shaders/gouraud.fs");
	entity[1].entityMaterial.Kd = {1, 0.8, 0.6};
	entity[1].entityMaterial.Ka = {1, 0.8, 0.6};
	entity[1].entityMaterial.Ks = {0.2, 0.2, 0.2};
	entity[1].entityMaterial.shininess = 50;

	//LAB4
	Matrix44 mymodel3;
	Mesh* mymesh3 = new Mesh();
	mymesh3->LoadOBJ("..//res/meshes/lee.obj");
	entity[2].model = mymodel3;
	entity[2].mesh = mymesh3;
	entity[2].entityMaterial.materialTexture = Texture::Get("../res/textures/lee_color_specular.tga");
	entity[2].entityMaterial.shader = Shader::Get("../res/shaders/phong.vs", "../res/shaders/phong.fs");
	entity[2].entityMaterial.Kd = {1, 0.8, 0.6};
	entity[2].entityMaterial.Ka = {1, 0.8, 0.6};
	entity[2].entityMaterial.Ks = {0.2, 0.2, 0.2};
	entity[2].entityMaterial.shininess = 50;



	//CREAR CAMARA
	myCamera.eye = { 0,0,1 };
	myCamera.center = { 0,0,0 };
	myCamera.up = { 0,1,0 };
	myCamera.type = 0;
	myCamera.far_plane = 100;
	myCamera.near_plane = 0.01;
	myCamera.fov = PI / 4;
	myCamera.SetPerspective(myCamera.fov, window_width / window_height, myCamera.near_plane, myCamera.far_plane);
	//lights[0] = {(0.8,10,0), (100,100,100)};
	lights[0].intensity = { 1, 1, 0 };
	lights[0].Position = { 0, 0, 1 };
	Ia = {0.05, 0.05, 0.05};
	
}

// Render one frame
void Application::Render(void) {

	//zBuffer.width = framebuffer.width;
	//zBuffer.height = framebuffer.height;
	//zBuffer.pixels = new float[framebuffer.width * framebuffer.height];
	//zBuffer.Fill(FLT_MAX);
	//framebuffer.Fill(Color::BLACK);

	myCamera.LookAt(myCamera.eye, myCamera.center, myCamera.up);
	myCamera.SetPerspective(myCamera.fov, window_width / window_height, myCamera.near_plane, myCamera.far_plane);
	//Gouroud
	uniformData[0] = {myCamera.viewprojection_matrix, entity[1].model,Ia, entity[1].entityMaterial.materialTexture, lights[0].intensity, lights[0].Position, myCamera.eye};
	//Phong
	uniformData[1] = { myCamera.viewprojection_matrix, entity[2].model,Ia, entity[2].entityMaterial.materialTexture, lights[0].intensity, lights[0].Position, myCamera.eye};
	//
	//if (mode == 1) { entity4.Render(&framebuffer, &myCamera, &zBuffer,zBufferOn,InterpolatedUV,Color::WHITE); }
	//
	//else if (mode == 2) {
	//	entity.Render(&framebuffer, &myCamera, &zBuffer,zBufferOn, InterpolatedUV, Color::WHITE);
	//	entity2.Render(&framebuffer, &myCamera,&zBuffer,zBufferOn,InterpolatedUV,Color::GREEN);
	//	entity3.Render(&framebuffer, &myCamera,&zBuffer,zBufferOn, InterpolatedUV,Color::BLUE);
	//}

	//framebuffer.Render();

	//LAB4
	if (u_lab == 4.0) {
		if (u_task == 4.0) {

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			entity[0].meshShader->Enable();
			//entity4.meshShader->SetMatrix44("u_model", entity4.model);
			//entity4.meshShader->SetMatrix44("u_viewprojection", myCamera.viewprojection_matrix);
			//entity4.meshShader->SetFloat("u_time", time);
			entity[0].Render(&myCamera);
			entity[0].meshShader->Disable();
		}
		else {

			quadShader->Enable();

			quadShader->SetFloat("u_mode", u_mode);
			quadShader->SetFloat("u_task", u_task);
			quadShader->SetFloat("u_time", time);
			quadShader->SetTexture("u_texture", texture);

			quad.Render();

			quadShader->Disable();
		}
	}
	else {
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		
		switch ((int)u_mode)
		{
		case 7: entity[1].Render(uniformData[0]);break;
		case 8: entity[2].Render(uniformData[1]);break;
		}
	}
	
}

// Called after render
void Application::Update(float seconds_elapsed)
{


	
}

//keyboard press event 
void Application::OnKeyPressed(SDL_KeyboardEvent event)
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
	//case SDLK_PLUS: if (property == 1) {myCamera.near_plane += 0.01;}
	//				else if (property == 2) {myCamera.far_plane += 1;}
	//				else if (property == 3 && myCamera.fov<(PI+PI/18)) {myCamera.fov += PI/18;}break;
	//case SDLK_MINUS: if (property == 1 ) {myCamera.near_plane -= 0.01;}
	//				else if (property == 2 && myCamera.far_plane>0) {myCamera.far_plane -= 1;} 
	//				else if (property == 3 && myCamera.fov>PI/18) {myCamera.fov -= PI/18;}break;
	case SDLK_a: u_mode = 1.00; break;
	case SDLK_b: u_mode = 2.00; break;
	case SDLK_c: u_mode = 3.00; break;
	case SDLK_d: u_mode = 4.00; break;
	case SDLK_e: u_mode = 5.00; break;
	case SDLK_f: u_mode = 6.00; break;
	case SDLK_g: u_mode = 7.00; break;
	case SDLK_p: u_mode = 8.00; break;
	
	case SDLK_1: u_task = 1.00; break;
	case SDLK_2: u_task = 2.00; break;
	case SDLK_3: u_task = 3.00; break;
	case SDLK_4: u_task = 4.00; break;
	
	case SDLK_l: if (u_lab == 4.00) { u_lab = 5.00; }
			   else { u_lab = 4.00; }; break;
	}


}

void Application::OnMouseButtonDown(SDL_MouseButtonEvent event) {

	if (event.button == SDL_BUTTON_LEFT) {
		click = true;
	}
	if (event.button == SDL_BUTTON_RIGHT) {
		click2 = true;
	}
}

void Application::OnMouseButtonUp(SDL_MouseButtonEvent event)
{
	if (event.button == SDL_BUTTON_LEFT) {
		click = false;
	}
	if (event.button == SDL_BUTTON_RIGHT) {
		click2 = false;
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	if (click) {
		//EYE
		//Horizontal
		if (mouse_delta.x > 0) {
			myCamera.eye.x += mouse_delta.x / 500;
		}
		else if (mouse_delta.x < 0) {
			myCamera.eye.x += mouse_delta.x / 500;
		}
		//Vertical
		if (mouse_delta.y > 0 ) {
			myCamera.eye.y += mouse_delta.y / 500;
		}
		else if (mouse_delta.y < 0 ) {
			myCamera.eye.y += mouse_delta.y/ 500;
		}
	}
	//CENTER
	else if (click2) {
		if (mouse_delta.x > 0) {
			myCamera.center.x += mouse_delta.x / 500;
		}
		else if (mouse_delta.x < 0) {
			myCamera.center.x += mouse_delta.x / 500;
		}
		//Vertical
		if (mouse_delta.y > 0) {
			myCamera.center.y -= mouse_delta.y / 500;
		}
		else if (mouse_delta.y < 0) {
			myCamera.center.y -= mouse_delta.y / 500;
		}
	}
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	Vector3 direction = (myCamera.center - myCamera.eye);
	direction.Normalize();
	float dy = event.preciseY;
	myCamera.eye.x -= direction.x * (dy / 10);
	myCamera.eye.y -= direction.y * (dy / 10);
	myCamera.eye.z -= direction.z * (dy / 10);
		

	
	
	// ...
}

void Application::OnFileChanged(const char* filename)
{
	Shader::ReloadSingleShader(filename);
}