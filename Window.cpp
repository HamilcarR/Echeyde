#include "Window.h"
#include "Importer.h"
#include "Camera.h"
#include "Renderer.h"
#include "Light.h"
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
	glEnable(GL_CULL_FACE); 
	glCullFace(GL_BACK); 

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
	BaseShader *shader = new BaseShader(std::string("vertex.vert"), std::string("fragment.frag") , std::string("geometry.geom"));
	std::vector<object_data> st;
	
	try {
		st = Echeyde::FILEIO::Importer::load_model(std::string("cube.obj"));
	}
	catch (const File_not_found &e) {
		std::cout << e.what() << std::endl;
	}
	catch (const MaterialException &e) {
		std::cout << e.what() << std::endl;
	}
	catch (const Importer_Error &e) {
		std::cout << e.what() << std::endl;
	}
	
	Renderer *renderer = Renderer::getInstance();
	LightArray *instance = LightArray::getInstance();

	glm::mat4 projection = glm::perspective(75.f, float(HEIGHT/WIDTH), 0.001f, 1000.f); 
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); 
	glm::mat4 model = glm::mat4(1.); 
	//renderer->addDynamicMeshes(st,shader, true);
	
	shader_light_data data;
	data.base.position = glm::vec3(0, 3, 0); 
	data.attenuation = glm::vec3(10, 10, 100);
	data.radius = 100.f; 
	data.base.colour = glm::vec3(0.4, 0.07, 0.1); 
	data.base.power = 2000.F;
	instance->addLight(new PointLight(data.base,data.radius,data.attenuation ));
	renderer->addStaticMeshes(st, shader, true); 
	SDL_Event event; 
	std::unique_ptr<Camera> user_camera = std::unique_ptr<Camera>(new Camera(1.f, 1.f, glm::vec3(0, 1, 0), 75.f, float(HEIGHT / WIDTH), 0.001f, 1000.f)); 
	

	while (loop) {
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT)
				loop = false;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				loop= false;

			user_camera->Move(event);
		}
		//instance->getLightArray()[0]->setPosition(user_camera->getPosition());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer->renderStaticMeshes(user_camera->getProjectionMatrix(), model, user_camera->getViewMatrix()); 
	
		SDL_GL_SwapWindow(window); 
	}
	TextureArray::clean();
	renderer->destroy();
	instance->clean(); 
	delete shader;


	
}