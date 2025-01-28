#include "application.h"
#include "mesh.h"
#include "shader.h"
#include "utils.h" 

Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	int w,h;
	SDL_GetWindowSize(window,&w,&h);

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
	//LAB1
	/*
	for (int i = 0; i < ParticleSystem::MAX_PARTICLES; ++i) {
		p.particles[i].position.x = rand()% (framebuffer.width +1);
		p.particles[i].position.y = 700 + rand() % (100 +1) ;
		p.particles[i].velocity.y = - rand() %(50+1);
		p.particles[i].ttl = rand() %1000 +1 ;
		p.particles[i].inactive = false;
	}
	
	buttons[0].png.LoadPNG("../res/images/clear.png", true);
	buttons[1].png.LoadPNG("../res/images/load.png", true);
	buttons[2].png.LoadPNG("../res/images/save.png", true);
	buttons[3].png.LoadPNG("../res/images/eraser.png", true);
	buttons[4].png.LoadPNG("../res/images/line.png", true);
	buttons[5].png.LoadPNG("../res/images/rectangle.png", true);
	buttons[6].png.LoadPNG("../res/images/circle.png", true);
	buttons[7].png.LoadPNG("../res/images/triangle.png", true);
	buttons[8].png.LoadPNG("../res/images/black.png", true);
	buttons[9].png.LoadPNG("../res/images/white.png", true);
	buttons[10].png.LoadPNG("../res/images/pink.png", true);
	buttons[11].png.LoadPNG("../res/images/yellow.png", true);
	buttons[12].png.LoadPNG("../res/images/red.png", true);
	buttons[13].png.LoadPNG("../res/images/blue.png", true);
	buttons[14].png.LoadPNG("../res/images/cyan.png", true);
	buttons[15].png.LoadPNG("../res/images/green.png", true);
	buttons[16].png.LoadPNG("../res/images/pencil.png", true);
	*/

	//LAB2
	Matrix44 mymodel;
	Mesh* mymesh = new Mesh();
	mymesh->LoadOBJ("..res/meshes/lee.obj");

	entity.model = mymodel;
	entity.mesh = mymesh;

	//CREAR CAMARA
	//myCamera.LookAt(Vector3 On esta, Vector3 On mira, Vector3 up);
	//myCamera.SetPerspective(float FOV, float ASPECT, nearplane-- > 0.001, farplane 100);
}

// Render one frame
void Application::Render(void) {

	entity.Render(&framebuffer, myCamera, COlor);



	framebuffer.Render()
	/*
	if (mode == 1) {
		for (float i = 0; i < 2 * 3.14; i+=3.14 / 6) {
			framebuffer.DrawLineDDA(300, 300, 300 + 100 * cos(i), 300 + 100 * sin(i), current_color);
		}
		framebuffer.Render();
		framebuffer.Fill(Color::BLACK);
	}
	else if (mode == 2) {
		framebuffer.DrawRect(500, 500, 400, 100, Color::BLUE,border_width, isFilled, Color::RED);
		framebuffer.DrawRect(200, 200, 100, 100, Color::BLUE, 0, isFilled, Color::RED);
		framebuffer.DrawRect(600, 100, 100, 200, Color::BLUE, border_width, isFilled, Color::RED);
		framebuffer.Render();
		framebuffer.Fill(Color::BLACK);

	}
	else if(mode == 3) {
		framebuffer.DrawCircle(500, 400, 100, current_color, border_width, true, current_color);
		framebuffer.Render();
		framebuffer.Fill(Color::BLACK);
	}
	else if (mode == 4) {

		framebuffer.DrawTriangle( {200,100 }, { 300,600 }, { 100,300 }, Color::YELLOW, isFilled, Color::GREEN);
		framebuffer.DrawTriangle({ 500,100 }, { 700,600 }, { 600,300 }, Color::RED, isFilled, Color::RED);
		framebuffer.DrawTriangle({ 1100,300 }, { 900,500 }, { 1000,1300 }, Color::CYAN, isFilled, Color::PURPLE);
	
		framebuffer.Render();
		framebuffer.Fill(Color::BLACK);
	}
	else if (mode == 5) { // Paint
		
		framebuffer.Render();
		framebuffer.DrawRect(0, 0, framebuffer.width, 36, Color::BLACK, 0, true, Color::GRAY);

		for (int i = 0; i < 17;++i) {
			buttons[i].pos.x = i * 35;
			framebuffer.DrawImage(buttons[i].png, i * 35, 0);
		}

		if (left_click) {
			if (buttons[0].IsMouseInside(mouse_position)) {
				framebuffer.Fill(Color::BLACK);
			}
			else if (buttons[1].IsMouseInside(mouse_position)) {
				framebuffer.LoadTGA("Saved_Session", true);
			}
			else if (buttons[2].IsMouseInside(mouse_position)) {
				framebuffer.SaveTGA("Saved_Session");
			}
			else if (buttons[3].IsMouseInside(mouse_position)) {
				eraser = true;
				pencil = false;
			}
			else if (buttons[4].IsMouseInside(mouse_position)) {
				isActiveLine = true;
				click = 1;
				pencil = false;
				eraser = false;

			}
			else if (buttons[5].IsMouseInside(mouse_position)) {
				isActiveTriangle = false;
				isActiveRect = true;
				click = 1;
				pencil = false;
				eraser = false;
			}
			else if (buttons[6].IsMouseInside(mouse_position)) {
				isActiveCircle = true;
				pencil = false;
				eraser = false;
			}
			else if (buttons[7].IsMouseInside(mouse_position)) {
				isActiveRect = false;
				isActiveTriangle = true;
				click = 1;
				pencil = false;
				eraser = false;
			}
			else if (buttons[8].IsMouseInside(mouse_position)) {
				current_color = Color::BLACK;
				if (click > 0) {
					--click;
				}
			}
			else if (buttons[9].IsMouseInside(mouse_position)) {
				current_color = Color::WHITE;
				if (click > 0) {
					--click;
				}
			}
			else if (buttons[10].IsMouseInside(mouse_position)) {
				current_color = Color::PURPLE;
				if (click > 0) {
					--click;
				}
			}
			else if (buttons[11].IsMouseInside(mouse_position)) {
				current_color = Color::YELLOW;
				if (click > 0) {
					--click;
				}
			}
			else if (buttons[12].IsMouseInside(mouse_position)) {
				current_color = Color::RED;
				if (click > 0) {
					--click;
				}
			}
			else if (buttons[13].IsMouseInside(mouse_position)) {
				current_color = Color::BLUE;
				if (click > 0) {
					--click;
				}
			}
			else if (buttons[14].IsMouseInside(mouse_position)) {
				current_color = Color::CYAN;
				if (click > 0) {
					--click;
				}
			}
			else if (buttons[15].IsMouseInside(mouse_position)) {
				current_color = Color::GREEN;
				if (click > 0) {
					--click;
				}
			}
			else if (buttons[16].IsMouseInside(mouse_position)) {
				pencil = true;
				eraser = false;

			}
		}
		if (isActiveCircle && (click == 1)) {
			framebuffer.DrawCircle(mouse_position.x, mouse_position.y, 100, current_color, border_width, isFilled, current_color);
			isActiveCircle = false;
			click = 0;
		}
		if (click == 2 && uniqueMouseValue == 0) {
			startPolygon.x = mouse_position.x; //canvia constantment, no podem guardar el valor, canvia fins clicar (click=3), llavors la linia comença i acaba al mateix lloc
			startPolygon.y = mouse_position.y;
			uniqueMouseValue = 1;
		}
		else if ((click == 3)) {
			if (isActiveLine) { //Dibuixar linia
				framebuffer.DrawLineDDA(startPolygon.x, startPolygon.y, mouse_position.x, mouse_position.y, current_color);
				click = 0;
				isActiveLine = false;
				uniqueMouseValue = 0;
			}
			else if (isActiveRect) {  //dibuixar rectangle
				int width = mouse_position.x - startPolygon.x;
				int height = mouse_position.y - startPolygon.y;
				if ((width < 0) && (height < 0)) {
					framebuffer.DrawRect(mouse_position.x, mouse_position.y, -width, -height, current_color, border_width, isFilled, current_color);
				}
				else if (width < 0) {
					framebuffer.DrawRect(mouse_position.x, startPolygon.y, -width, height, current_color, border_width, isFilled, current_color);
				}
				else if (height < 0) {
					framebuffer.DrawRect(startPolygon.x, mouse_position.y, width, -height, current_color, border_width, isFilled, current_color);
				}
				else {
					framebuffer.DrawRect(startPolygon.x, startPolygon.y, width, height, current_color, border_width, isFilled, current_color);
				}
				click = 0;
				isActiveRect = false;
				uniqueMouseValue = 0;
			}
			else if ((isActiveTriangle) && (uniqueMouseValue == 1)) {  //Guardem segon punt triangle
				secondPointTriagle = mouse_position;
				uniqueMouseValue = 0;
			}
		}
		else if ((click == 4)) {
			framebuffer.DrawTriangle(startPolygon, secondPointTriagle, mouse_position, current_color, isFilled, current_color);
			isActiveTriangle = false;
			click = 0;
		}
		if ((eraser) && (mouse_position.y > 36) && (left_click)) {
			framebuffer.SetPixel((int)mouse_position.x, (int)mouse_position.y, Color::BLACK);;
		}
		if (pencil && (mouse_position.y > 36) && left_click) {//Dibuixar pencil
			framebuffer.SetPixel((int)mouse_position.x, (int)mouse_position.y, current_color);
		}
	}
	else if(mode==6){ // Animacio
		
		for (int i = 0; i < ParticleSystem::MAX_PARTICLES;++i) {
			framebuffer.SetPixel(p.particles[i].position.x, p.particles[i].position.y, p.particles[i].color);
		}
		framebuffer.Render();
		framebuffer.Fill(Color::BLACK);
	}
	*/

}

// Called after render
void Application::Update(float seconds_elapsed)
{
	if (mode == 6) {
		for (int i = 0; i < ParticleSystem::MAX_PARTICLES; ++i) {
			if (p.particles[i].inactive == false) {
				p.particles[i].position.y += p.particles[i].velocity.y * seconds_elapsed;
				p.particles[i].ttl -= seconds_elapsed;
				if (p.particles[i].ttl == 0) {
					p.particles[i].inactive = true;
				}
			}


		}
	}
	
}

//keyboard press event 
void Application::OnKeyPressed(SDL_KeyboardEvent event)
{
	// KEY CODES: https://wiki.libsdl.org/SDL2/SDL_Keycode
	switch (event.keysym.sym) {
	case SDLK_ESCAPE: exit(0); break; // ESC key, kill the app
	case SDLK_PLUS: border_width += 1;  break;
	case SDLK_MINUS: if (border_width > 0) {
		border_width -= 1;
	}  break;
	case SDLK_1: mode = 1; break;
	case SDLK_2: mode = 2; break;
	case SDLK_3: mode = 3; break;
	case SDLK_4: mode = 4; break;
	case SDLK_5: mode = 5; break;
	case SDLK_6: mode = 6; break;
	case SDLK_f: if (isFilled) { isFilled = false; }
			   else { isFilled = true; }break;
	}
}

	void Application::OnMouseButtonDown(SDL_MouseButtonEvent event) {

		if (event.button == SDL_BUTTON_LEFT) {
			left_click = true;
			if (isActiveLine || isActiveRect || isActiveTriangle||isActiveCircle) {
				click += 1;
			}
			
			
		}
	}

void Application::OnMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) {
		left_click = false;
		
	}
}

void Application::OnMouseMove(SDL_MouseButtonEvent event)
{
	
}

void Application::OnWheel(SDL_MouseWheelEvent event)
{
	float dy = event.preciseY;

	// ...
}

void Application::OnFileChanged(const char* filename)
{ 
	Shader::ReloadSingleShader(filename);
}