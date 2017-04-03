#ifndef WINDOW_H
#define WINDOW_H
#include "KInputs.h"
#include "Scene.h"
#include "Constants.h"
#include "Shader.h"
/*The main class,manage all 3D objects*/

struct Dim {
	Uint16 width; 
	Uint16 height; 
};

class Window {

public:
	Window(const std::string name , Uint16 width , Uint16 height , KInputs &inputs , Echeyde::Scene &scene);
	virtual ~Window(); 
	Dim getDimensions();
	void Loop(); 

private:
	SDL_Window* window; 
	SDL_GLContext context; 
	Dim dimensions; 
	KInputs *input; 
	bool loop; 
	Echeyde::Scene *scene;

};




#endif // !WINDOW_H
