#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 
#include "Entity.h"

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
	//LAB2

	Matrix44 mymodel;
	Mesh* mymesh = new Mesh();
	mymesh->LoadOBJ("..//res/meshes/lee.obj");
	entity.model = mymodel;
	entity.mesh = mymesh;
	
	Matrix44 mymodel2;
	Mesh* mymesh2 = new Mesh();
	mymesh2->LoadOBJ("..//res/meshes/lee.obj");
	entity2.model = mymodel2;
	entity2.mesh = mymesh2;

	Matrix44 mymodel3;
	Mesh* mymesh3 = new Mesh();
	mymesh3->LoadOBJ("..//res/meshes/lee.obj");
	entity3.model = mymodel3;
	entity3.mesh = mymesh3;

	Matrix44 mymodel4;
	Mesh* mymesh4 = new Mesh();
	mymesh4->LoadOBJ("..//res/meshes/lee.obj");
	entity4.model = mymodel4;
	entity4.mesh = mymesh4;
	
	Image *mytexture = new Image();
	mytexture->LoadTGA("..//res/textures/lee_color_specular.tga",true);
	entity4.texture = mytexture;
	
	entity4.n = entity4.texture;
	entity4.zbufferTemp = &zBuffer;
	entity2.model.Translate(-0.5,-0.3,0);
	entity3.model.Translate(0.5, 0, 0);
	//CREAR CAMARA
	myCamera.eye = { 0,0,1};
	myCamera.center = { 0,0,0 };
	myCamera.up = { 0,1,0 };
	myCamera.type = 0;
	myCamera.far_plane = 100;
	myCamera.near_plane = 0.01;
	myCamera.fov = PI / 4;
	myCamera.SetPerspective(myCamera.fov, window_width / window_height, myCamera.near_plane, myCamera.far_plane);
}

// Render one frame
void Application::Render(void) {

	zBuffer.width = framebuffer.width;
	zBuffer.height = framebuffer.height;
	zBuffer.pixels = new float[framebuffer.width * framebuffer.height];
	zBuffer.Fill(FLT_MAX);
	framebuffer.Fill(Color::BLACK);

	myCamera.LookAt(myCamera.eye, myCamera.center, myCamera.up);
	myCamera.SetPerspective(myCamera.fov, window_width / window_height, myCamera.near_plane, myCamera.far_plane);

	
	if (mode == 1) { entity4.Render(&framebuffer, &myCamera, &zBuffer,zBufferOn,InterpolatedUV,Color::WHITE); }
	
	else if (mode == 2) {
		entity.Render(&framebuffer, &myCamera, &zBuffer,zBufferOn, InterpolatedUV, Color::WHITE);
		entity2.Render(&framebuffer, &myCamera,&zBuffer,zBufferOn,InterpolatedUV,Color::GREEN);
		entity3.Render(&framebuffer, &myCamera,&zBuffer,zBufferOn, InterpolatedUV,Color::BLUE);
	}

	framebuffer.Render();

	

}

// Called after render
void Application::Update(float seconds_elapsed)
{

	//LAB2
	if (mode == 2) {
		entity.Update(seconds_elapsed);
		entity2.Update2(seconds_elapsed);
		entity3.Update3(seconds_elapsed);
	}

	
}

//keyboard press event 
void Application::OnKeyPressed(SDL_KeyboardEvent event)
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
	case SDLK_PLUS: if (property == 1) {myCamera.near_plane += 0.01;}
					else if (property == 2) {myCamera.far_plane += 1;}
					else if (property == 3 && myCamera.fov<(PI+PI/18)) {myCamera.fov += PI/18;}break;
	case SDLK_MINUS: if (property == 1 ) {myCamera.near_plane -= 0.01;}
					else if (property == 2 && myCamera.far_plane>0) {myCamera.far_plane -= 1;} 
					else if (property == 3 && myCamera.fov>PI/18) {myCamera.fov -= PI/18;}break;
	case SDLK_1: mode = 1; break;
	case SDLK_2: mode = 2; break;
	case SDLK_n: property = 1; break;
	case SDLK_f: property = 2;break;
	case SDLK_v: property= 3;break;
	case SDLK_t: entity4.textureOn = !entity4.textureOn;break;
	case SDLK_z: zBufferOn =!zBufferOn;break;
	case SDLK_c: InterpolatedUV = !InterpolatedUV;break;
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