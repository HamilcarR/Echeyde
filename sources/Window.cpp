#include "../headers/Window.h"
#include "../headers/Importer.h"
#include "../headers/Camera.h"
#include "../headers/Renderer.h"
#include "../headers/Light.h"
#include "../headers/GameObject.h"
#include "../headers/Terrain.h"
#include "../headers/Skybox.h"
#include "../headers/Framebuffer.h"
#include "../headers/GUI.h"
#include <SOIL/SOIL.h>

Window::Window(const std::string name , Uint16 width , Uint16 height,KInputs inputs , Echeyde::Scene sc)
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
	GLenum erno = glewInit();
	if (erno != GLEW_OK) {
		std::cout << "GLEW initialization fucked up!" << "\n";
		SDL_GL_DeleteContext(context); 
		SDL_DestroyWindow(window); 
		SDL_Quit(); 
	}
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
	std::string A("vertex.vert");
	std::string B("fragment.frag");
	std::string C("geometry.geom");

	BaseShader *shader = new BaseShader(A , B , C);
	 A = "terrain.vert";
	 B = "terrain.frag";
	 C = "terrain.geom";
	BaseShader *terrain_shader = new BaseShader(A , B , C); 
	 A = "depth.vert";
 	 B = "depth.frag";
	Shader* shadowShader = new BaseShader(A , B); 
	 A = "gui.vert";
	 B = "gui.frag"; 
	BaseShader gui(A , B); 
	std::vector<object_data> st;
	std::vector<object_data> si, sb ; 
	SkyboxShader skybox_shader("skybox.vert", "skybox.frag");
	Skybox skybox(SKYBOX_LOCATION + "sky.dds", skybox_shader);
	terrain_data_struct terrain_geometry = TerrainGenerator::generateTerrain("heightmap.png");

	//geometry_data terrain_g = TerrainGenerator::generateTerrain(10);
	//terrain_data_struct terrain_geometry;
	//terrain_geometry.terrain_data = terrain_g; 
	assert(terrain_shader!=nullptr); 	
	Renderer *renderer = Renderer::getInstance();
	LightArray *lights = LightArray::getInstance();
	
	Framebuffer shadowframebuffer(1024, 1024); 
	Texture A1 ( shadowframebuffer.getDepthTexture() , "shadow"); 
	st = Echeyde::FILEIO::Importer::load_model("Boombox.gltf" , false) ; 
	si = Echeyde::FILEIO::Importer::load_model("cottage.obj" , false); 
	sb = Echeyde::FILEIO::Importer::load_model("wood.obj" , false) ; 

	GameObject wood = GameObject(sb , shader , true , false); 
	wood.translate(glm::vec3(653 , -20 , 606)); 
	wood.scale(glm::vec3(2 , 2 , 2)); 
	wood.setTexture(A1 , Echeyde::SHADOWMAP0) ; 
	
	GameObject box = GameObject(st , shader , true , false); 
	box.scale(glm::vec3(10 , 10 , 10));
	box.translate(glm::vec3(584 , 0 , 659)) ; 

	GameObject house = GameObject(si , shader , true , false);
	house.scale(glm::vec3(3 , 3 , 3));
	house.translate(glm::vec3(589 , -10 , 638)); 
	house.setTexture(A1 , Echeyde::SHADOWMAP0) ; 

		material_data mat_data ;
		object_data terrain_obj;
		mat_data.transparency = false; 
		terrain_obj.data = terrain_geometry.terrain_data;
		mat_data.textures.diffuse = TEXTURES_LOCATION +"dirt.png";
		mat_data.textures.opacity = TEXTURES_LOCATION + "blendmap.png";
		mat_data.textures.normal = TEXTURES_LOCATION  + "gravel.png";
		mat_data.textures.optional = TEXTURES_LOCATION + "snow.png" ;
		mat_data.textures.blend = TEXTURES_LOCATION + "grass.png";
		
		terrain_obj.material = mat_data; 
		std::vector<object_data> ob; 
		ob.push_back(terrain_obj); 
		Terrain terrain = Terrain(ob, terrain_shader, true, true , terrain_geometry.collision_map);

		terrain.setTexture(A1, Echeyde::SHADOWMAP0);
		


	//GameObject obj2 = GameObject(si, shader, true, false);
	shader_light_data data;

	//light_view.setPosition(glm::vec3(500, 90, 300), glm::vec3(300, 90, 200)); 
		

	
		data.base.position = glm::vec3(500, 20.2, 500);
		data.attenuation = glm::vec3(10, 100, 3000);
		data.radius = 10000.f;
		data.base.colour = glm::vec3(0.3, 0.1, 0.2);
		data.base.power = 1.F;
		lights->addLight(new PointLight(data.base, data.radius, data.attenuation));


		data.base.position = glm::vec3(300 ,1000, 300);
		data.base.colour = glm::vec3(0.3, 0.25, 0.31);
		data.base.power = 1.F;
		lights->addLight(new DirectionalLight(data.base));
	//	
		data.base.position = glm::vec3(658, 10, 638);
		data.attenuation = glm::vec3(10, 10, 100);
		data.radius = 10.f;
		data.base.colour = glm::vec3(0.4, 0.5, 0.45);
		data.base.power = 500.3F;
		lights->addLight(new PointLight(data.base, data.radius, data.attenuation));
		
		data.base.position = glm::vec3(400, 31, 400);
		data.attenuation = glm::vec3(1, 10, 10);
		data.radius = 1.f;
		data.base.colour = glm::vec3(0.5, 0.2, 0.4);
		data.base.power =1.F;
		lights->addLight(new PointLight(data.base, data.radius, data.attenuation));
		
		data.base.position = glm::vec3(500, 20.2, 100);
		data.attenuation = glm::vec3(1, 10, 100);
		data.radius = 10000.f;
		data.base.colour = glm::vec3(0.6, 0.1, 0.7);
		data.base.power = 1.F;
		lights->addLight(new PointLight(data.base, data.radius, data.attenuation));

		data.base.position = glm::vec3(200, 20.2, 500);
		data.attenuation = glm::vec3(1, 10, 30);
		data.radius = 10000.f;
		data.base.colour = glm::vec3(0.6, 0.1, 0.7);
		data.base.power = 1.F;
		lights->addLight(new PointLight(data.base, data.radius, data.attenuation));


		
		
			
	Camera user_camera =  Camera(5.f, 5.f, glm::vec3(0, 1, 0), 120.f, float(17/9), 0.1f, 5000.f);
	user_camera.setPosition(glm::vec3(500, 90, 300));
	
	SDL_Event event; 
	float i = 500 , j = 500 , k = 21 , pow = 0.1 , ro = 0. , a1 = 1 , a2 = 10 , a3 = 100; 

	while (loop) {
		GLuint t1 = SDL_GetTicks(); 
	SDL_GL_SwapWindow(window); 
	


	PointLight *P = static_cast<PointLight*>(lights->getLightArray()[1]);
		while (SDL_PollEvent(&event)) {
			
			if (event.type == SDL_QUIT)
				loop = false;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				loop= false;
			if (event.key.keysym.sym == SDLK_KP_8)
				i+=0.5f ;
			if (event.key.keysym.sym == SDLK_KP_2)
				i-=0.5f ;
			if (event.key.keysym.sym == SDLK_KP_4)
				j += 0.5f ;
			if (event.key.keysym.sym == SDLK_KP_6)
				j -= 0.5f ;
			if (event.key.keysym.sym == SDLK_KP_9)
				k += 0.5f ; 
			if (event.key.keysym.sym == SDLK_KP_3)
				k -= 0.5f ;
			if (event.key.keysym.sym == SDLK_KP_PLUS)
				pow += 5 ; 
			if (event.key.keysym.sym == SDLK_KP_MINUS)
				pow -= 5 ;
			if (event.key.keysym.sym == SDLK_KP_1)
				ro -= 0.5f ; 
			if (event.key.keysym.sym == SDLK_KP_7)
				ro += 0.5f ; 
			if (event.key.keysym.sym == SDLK_o)
				a1 += 0.01f ; 
			if (event.key.keysym.sym == SDLK_l)
				a1 -= 0.01f ; 
			if (event.key.keysym.sym == SDLK_m)
				a2 -= 0.01f ;
			if (event.key.keysym.sym == SDLK_p)
				a2 += 0.01f ; 
			if (event.key.keysym.sym == SDLK_i)
				a3 += 1.f ; 
			if (event.key.keysym.sym == SDLK_k)
				a3 -= 1.f ; 
			if (event.key.keysym.sym == SDLK_f)
				SOIL_save_screenshot("screenshot.bmp", SOIL_SAVE_TYPE_BMP, 0, 0, 1920, 1080); 
			user_camera.Move(event);
		}
	glm::vec3 pos(i , k , j) ;
	PointLight * plight = static_cast<PointLight*>(lights->getLightArray()[0]); 
	glm::vec3 campos = user_camera.getPosition() ;

	//plight->setPosition(campos.x , campos.y , campos.z) ; 
	glm::vec3 lpos = plight->getPosition() ;
//	plight->setAttenuation(glm::vec3(a1 , a2 , a3)); 
	plight->setPower(pow) ; 
	ViewCamera light_view(-200.f, 200.f, -200.f, 200.f, 1.f, 10000.f,glm::vec3(0,1,0)); 
	light_view.setPosition((P->getPosition()+pos)-glm::vec3(50,50,50), pos);
	renderer->renderShadowMap(light_view, shadowframebuffer, shadowShader); 
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer->renderAll(user_camera, &skybox , light_view);

	GLuint t2 = SDL_GetTicks(); 
	}
	TextureArray::clean();
	shadowframebuffer.clean(); 
	skybox.clean(); 
	renderer->destroy();
	lights->clean();
	shadowShader->clean();
	delete shadowShader; 
	delete shader;
	delete terrain_shader; 


	
}
