/*  
	+ This class encapsulates the application, is in charge of creating the data, getting the user input, process the update and render.
*/

#pragma once

#include "main/includes.h"
#include "framework.h"
#include "image.h"

class Button {
public:
	Vector2 pos;
	Image png;

	bool IsMouseInside(Vector2 mousePosition) {
		if ((mousePosition.x < png.width + pos.x) && (mousePosition.y < png.height + pos.y) && (mousePosition.x > pos.x) && (mousePosition.y > pos.y)) {
			return true; 
		}
		else { return false; }
	}

};

class ParticleSystem {
public:
	static const int MAX_PARTICLES =1000;

	struct Particle {
		Vector2 position;
		Vector2 velocity; // Normalized speed and direction of the particle
		Color color = Color::WHITE;
		float acceleration;
		float ttl; // Time left until the particle expires
		bool inactive = false; // Particle is not used/expired, so it can be recreated
	};

	Particle particles[MAX_PARTICLES];


	void Init();
	void Render(Image* framebuffer);
	void Update(float dt);
};

class Application
{
public:
	int border_width = 1;
	Color current_color = Color::YELLOW;
	
	int click = 0;
	int uniqueMouseValue = 0;
	int mode;
	
	bool eraser = false;
	bool left_click = false;
	bool pencil = false;
	bool isActiveLine = false;
	bool isActiveRect = false;
	bool isActiveTriangle = false;
	bool isActiveCircle = false;
	bool isFilled = false;

	Button buttons[17];
	ParticleSystem p;
	Vector2 startPolygon;
	Vector2 secondPointTriagle;
	// Window

	SDL_Window* window = nullptr;
	int window_width;
	int window_height;

	float time;

	// Input
	const Uint8* keystate;
	int mouse_state; // Tells which buttons are pressed
	Vector2 mouse_position = {0.0,0.0}; // Last mouse position
	Vector2 mouse_delta; // Mouse movement in the last frame

	void OnKeyPressed(SDL_KeyboardEvent event);
	void OnMouseButtonDown(SDL_MouseButtonEvent event);
	void OnMouseButtonUp(SDL_MouseButtonEvent event);
	void OnMouseMove(SDL_MouseButtonEvent event);
	void OnWheel(SDL_MouseWheelEvent event);
	void OnFileChanged(const char* filename);

	// CPU Global framebuffer
	Image framebuffer;

	// Constructor and main methods
	Application(const char* caption, int width, int height);
	~Application();

	void Init( void );
	void Render( void );
	void Update( float dt );

	// Other methods to control the app
	void SetWindowSize(int width, int height) {
		glViewport( 0,0, width, height );
		this->window_width = width;
		this->window_height = height;
		this->framebuffer.Resize(width, height);
	}

	Vector2 GetWindowSize()
	{
		int w,h;
		SDL_GetWindowSize(window,&w,&h);
		return Vector2(float(w), float(h));
	}
};
