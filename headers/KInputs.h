#pragma once
/*Game loop class and events */
#include "Constants.h"
enum EVKEY : unsigned {Z = 0 , S = 1 , D = 2 , Q = 3 , K8 };
class KInputs
{
public:
	KInputs(SDL_Event &event);
	virtual ~KInputs();
	bool Loop(); 


private:
	bool key_array[EVENT_ARRAY_SIZE]; 
	SDL_Event event;
};

