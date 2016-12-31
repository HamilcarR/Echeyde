#include "KInputs.h"



KInputs::KInputs(SDL_Event& ev)
{
	key_array[EVENT_ARRAY_SIZE] = { false }; 
	event = ev;
}


KInputs::~KInputs()
{
}


bool KInputs::Loop() {

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT)
			return false;
		if (event.key.keysym.sym == SDLK_ESCAPE)
			return false;


	}

	return true;


}