#include "Window.h"
#include "Importer.h"
#include "Camera.h"
#include "Renderer.h"
#include "Light.h"
#include "GameObject.h"
#include "Terrain.h"
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
	BaseShader *terrain_shader = new BaseShader(std::string("terrain.vert"), std::string("terrain.frag"), std::string("terrain.geom")); 
	std::vector<object_data> st;
	std::vector<object_data> si;
	try {
		st = Echeyde::FILEIO::Importer::load_model(std::string("cube.obj"),false);
		si = Echeyde::FILEIO::Importer::load_model(std::string("sphere.obj"),false);
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
	glm::mat4 model = glm::scale(glm::vec3(5, 5, 5)); //glm::mat4(1.);
	
	//renderer->addDynamicMeshes(st,shader, true);
	GameObject object = GameObject(st, shader, true, true);
	GameObject obj2 = GameObject(si, shader, true, false);
	shader_light_data data;
		

		data.base.position = glm::vec3(3, 7, 0);
		data.attenuation = glm::vec3(1, 10, 100);
		data.radius = 100.f;
		data.base.colour = glm::vec3(0.1, 0.4, 0.6);
		data.base.power = 100.F;
		instance->addLight(new PointLight(data.base, data.radius, data.attenuation));


		data.base.position = glm::vec3(3, -7, 0);
		data.attenuation = glm::vec3(1, 100, 10);
		data.radius = 100.f;
		data.base.colour = glm::vec3(0.1, 0.5, 0.1);
		data.base.power = 50.F;
		instance->addLight(new PointLight(data.base, data.radius, data.attenuation));

		data.base.position = glm::vec3(10, -7, 3);
		data.attenuation = glm::vec3(1, 10, 10);
		data.radius = 100.f;
		data.base.colour = glm::vec3(0.6, 0.3, 0.1);
		data.base.power = 70.F;
		instance->addLight(new PointLight(data.base, data.radius, data.attenuation));

		
		geometry_data terrain_geometry = TerrainGenerator::generateTerrain(200);
		material_data mat_data = Echeyde::FILEIO::Importer::getMaterial(std::string("terrain.obj") , true);
		object_data terrain_obj;
		terrain_obj.data = terrain_geometry; 
		terrain_obj.material = mat_data; 
		std::vector<object_data> ob; 
		ob.push_back(terrain_obj); 
		GameObject terrain = GameObject(ob, terrain_shader, true, true);
		terrain.translate(glm::vec3(-100, 0, -100));
	
	//renderer->addStaticMeshes(st, shader, true); 

	SDL_Event event; 
	std::unique_ptr<Camera> user_camera = std::unique_ptr<Camera>(new Camera(1.f, 1.f, glm::vec3(0, 1, 0), 75.f, float(HEIGHT / WIDTH), 0.001f, 1000.f)); 
	float i = 0; 

	while (loop) {
		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_QUIT)
				loop = false;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				loop= false;
			user_camera->Move(event);
			if (event.key.keysym.sym == SDLK_KP_8)
				i++;
			if (event.key.keysym.sym == SDLK_KP_2)
				i--;
				
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		obj2.translate(glm::vec3(i,0,0));

		renderer->renderAll(user_camera->getProjectionMatrix(), user_camera->getViewMatrix()); 
	
		SDL_GL_SwapWindow(window); 
	}
	TextureArray::clean();
	renderer->destroy();
	instance->clean(); 
	delete shader;
	delete terrain_shader; 


	
}