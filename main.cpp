#include "Constants.h"
#include "View.h"
#include "Window.h"
#include "KInputs.h"






void Init_SDL(); 



int main(int arg_number, char** arg) {

	Init_SDL(); 
	SDL_Event event;
	KInputs main_loop(event);
	Echeyde::Scene scene; 
	Window window("window", WIDTH, HEIGHT,main_loop,scene); 
	
	window.Loop(); 


	SDL_Quit(); 

	return EXIT_SUCCESS;
}



void Init_SDL() {
	int err = SDL_Init(SDL_INIT_EVERYTHING); 
	if (err < 0) {
		std::cout << "SDL initialization failed  : " << SDL_GetError() << "\n";
	}
	else {
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 2);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	}

	
	

	}

void Quit_SDL() {
	
	SDL_Quit(); 
}