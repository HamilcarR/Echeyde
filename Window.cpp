#include "Window.h"
#include "Importer.h"


Window::Window(const std::string name , Uint16 width , Uint16 height,KInputs &inputs , Echeyde::Scene &sc)
{
	dimensions.height = height; 
	dimensions.width = width; 
	input = &inputs; 
	window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "Window Creation error !" << "\n";
		SDL_Quit();
	}
	context = SDL_GL_CreateContext(window); 
	if (context == 0) {
		std::cout << "Context creation error !" << "\n"; 
		SDL_DestroyWindow(window); 
		SDL_Quit(); 
	}
#ifdef WIN32
	GLenum erno = glewInit();
	if (erno != GLEW_OK) {
		std::cout << "GLEW initialization fucked up!" << "\n";
		SDL_GL_DeleteContext(context); 
		SDL_DestroyWindow(window); 
		SDL_Quit(); 
	}
#endif 
	loop = true;
	scene = &sc;
	glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
	SDL_GL_DeleteContext(context); 
	SDL_DestroyWindow(window); 

}

Dim Window::getDimensions() {
	
	return dimensions;

}

void Window::Loop() {
	Shader shader(std::string("vertex.vert"), std::string("fragment.frag") , std::string("geometry.geom"));
	object_data st;
	
	try {
		st = Echeyde::FILEIO::Importer::load_OBJ(std::string("cube"));
	}
	catch (const File_not_found &e) {
		std::cout << e.what() << std::endl;
	}
	catch (const MaterialException &e) {
		std::cout << e.what() << std::endl;
	}
	
	Material material(shader);
	
	vertex_data data;
	data.vertex = cube; 
	data.color = color; 
	data.indices = indice;
	Mesh mesh(data, material,true); 
	glm::mat4 projection = glm::perspective(70.f, 0.5f, 0.001f, 1000.f); 
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, -10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); 
	glm::mat4 model = glm::mat4(1.); 
	while (loop) {
		loop = input->Loop();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		mesh.display(projection,model,view); 
		


		SDL_GL_SwapWindow(window); 
	}



	
}