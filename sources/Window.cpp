#include "../headers/Window.h"
#include "../headers/Importer.h"
#include "../headers/Camera.h"
#include "../headers/Renderer.h"
#include "../headers/Light.h"
#include "../headers/GameObject.h"
#include "../headers/Terrain.h"
#include "../headers/Skybox.h"
#include "../headers/Framebuffer.h"
#include <SOIL\SOIL.h>

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
	Shader* shadowShader = new BaseShader(std::string("depth.vert"), std::string("depth.frag")); 
	BaseShader gui(std::string("gui.vert"), std::string("gui.frag")); 
	std::vector<object_data> st;
	std::vector<object_data> si, sb ; 
	SkyboxShader skybox_shader("skybox.vert", "skybox.frag");
	Skybox skybox(SKYBOX_LOCATION + "test.dds", skybox_shader);
	geometry_data terrain_geometry = TerrainGenerator::generateTerrain("heightmap.png");

	//geometry_data terrain_geometry = TerrainGenerator::generateTerrain(900);
	try {
	st = Echeyde::FILEIO::Importer::load_model(std::string("cube.obj"),true);
    si = Echeyde::FILEIO::Importer::load_model(std::string("objects.obj"),false);
	sb = Echeyde::FILEIO::Importer::load_model(std::string("house.obj"), false); 
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
	LightArray *lights = LightArray::getInstance();
	
	Framebuffer framebuffer(WIDTH, HEIGHT);
	Framebuffer shadowframebuffer(8102, 8102); 
	Texture A ( shadowframebuffer.getDepthTexture() , "shadow"); 
//	ViewCamera light_view(70.f, float(WIDTH / HEIGHT), 0.1f, 2000.f, glm::vec3(0, 1, 0));


//	GameObject sun = GameObject(sb, shader, true, true);
//	sun.scale(glm::vec3(10, 10, 10)); 
	GameObject cube = GameObject(st, &gui, true, false);
	GameObject house = GameObject(sb, shader, true, false);
	house.scale(glm::vec3(10, 10, 10));
	GameObject objects = GameObject(si, shader, true, true);
	
	objects.setTexture(A, Echeyde::SHADOWMAP0); 
	objects.translate(glm::vec3(430, 1, 430));
	cube.setTexture(A, Echeyde::DIFFUSE0);


		material_data mat_data ;
		object_data terrain_obj;
		mat_data.transparency = false; 
		terrain_obj.data = terrain_geometry;
		mat_data.textures.diffuse = TEXTURES_LOCATION + "/ground" + "/dirt" + "/dirt_01.png";
		mat_data.textures.opacity = TEXTURES_LOCATION + "/blendmaps" + "/blend.png";
		mat_data.textures.normal = TEXTURES_LOCATION + "/ground" + "/gravel_01.png";
		mat_data.textures.optional = TEXTURES_LOCATION + "/ground" + "/snow" + "/snow_1.png";
		mat_data.textures.blend = TEXTURES_LOCATION + "/ground" + "/grass" + "/grass_02.png";
		
		terrain_obj.material = mat_data; 
		std::vector<object_data> ob; 
		ob.push_back(terrain_obj); 
		GameObject terrain = GameObject(ob, terrain_shader, true, true);

		terrain.setTexture(A, Echeyde::SHADOWMAP0);



	//GameObject obj2 = GameObject(si, shader, true, false);
	shader_light_data data;

	//light_view.setPosition(glm::vec3(500, 90, 300), glm::vec3(300, 90, 200)); 
		

	
	/*	data.base.position = glm::vec3(10, 2, 3);
		data.attenuation = glm::vec3(1, 10, 100);
		data.radius = 100.f;
		data.base.colour = glm::vec3(0.6, 0.4, 0.2);
		data.base.power = 50.F;
		lights->addLight(new PointLight(data.base, data.radius, data.attenuation));*/


		data.base.position = glm::vec3(300 ,300, 300);
		data.base.colour = glm::vec3(1., 1., 1.);
		data.base.power = 0.2F;
		lights->addLight(new DirectionalLight(data.base));
		
	/*	data.base.position = glm::vec3(300, 5, 400);
		data.attenuation = glm::vec3(10, 100, 100);
		data.radius = 100.f;
		data.base.colour = glm::vec3(0.2, 0.3, 0.6);
		data.base.power = 700.F;
		lights->addLight(new PointLight(data.base, data.radius, data.attenuation));
		
		data.base.position = glm::vec3(301, 4, 201);
		data.attenuation = glm::vec3(10, 100, 100);
		data.radius = 100.f;
		data.base.colour = glm::vec3(0.6, 0.4, 0.3);
		data.base.power = 700.F;
		lights->addLight(new PointLight(data.base, data.radius, data.attenuation));
		*/

		
		
		cube.translate(glm::vec3(0.6, 0.6 , 0.1));
		cube.rotate(90, glm::vec3(1, 0, 0)); 
		cube.scale(glm::vec3(0.3, 0.1, 0.3)); 
		
	Camera user_camera =  Camera(5.f, 5.f, glm::vec3(0, 1, 0), 120.f, float(17/9), 0.1f, 5000.f);
	user_camera.setPosition(glm::vec3(500, 90, 300)); 
	SDL_Event event; 
	float i = 10 , j = 400 , k = 400 , pow = 50 , ro = 0.; 

	while (loop) {
	DirectionalLight *P = dynamic_cast<DirectionalLight*>(lights->getLightArray()[0]);
		while (SDL_PollEvent(&event)) {
			
			if (event.type == SDL_QUIT)
				loop = false;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				loop= false;
			if (event.key.keysym.sym == SDLK_KP_8)
				i+=1.5f;
			if (event.key.keysym.sym == SDLK_KP_2)
				i-=1.5f;
			if (event.key.keysym.sym == SDLK_KP_4)
				j += 1.5f;
			if (event.key.keysym.sym == SDLK_KP_6)
				j -= 1.5f;
			if (event.key.keysym.sym == SDLK_KP_9)
				k += 1.5f; 
			if (event.key.keysym.sym == SDLK_KP_3)
				k -= 1.5f;
			if (event.key.keysym.sym == SDLK_KP_PLUS)
				pow += 1.5f; 
			if (event.key.keysym.sym == SDLK_KP_MINUS)
				pow -= 1.5f;
			if (event.key.keysym.sym == SDLK_f)
				SOIL_save_screenshot("screenshot.bmp", SOIL_SAVE_TYPE_BMP, 0, 0, 1920, 1080); 
			user_camera.Move(event);
			user_camera.print_data(); 

		}
	

		cube.isDisplayed(false);

		glm::vec3 pos = user_camera.getPosition();
		house.translate(glm::vec3(j, i, k)); 
		objects.translate(glm::vec3(j+50, i, k+50));
		ro += 0.1f; 
		objects.rotate(ro, glm::vec3(0, 1, 0)); 
		ViewCamera light_view(-300.f, 300.f, -300.f, 300.f, 0.1f, 5000.f,glm::vec3(0,1,0)); 
		//light_view.setProjection(ViewCamera::getBoundingBox(user_camera , 200 , 20) , false); 
		light_view.setPosition(P->getPosition()+pos, pos);
	//sun.translate(light_view.getPosition()); 
	//sun.isDisplayed(false); 
	renderer->renderShadowMap(light_view, shadowframebuffer, shadowShader); 
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//	sun.isDisplayed(true); 
	cube.isDisplayed(false); 
	renderer->renderAll(user_camera, &skybox , light_view);

	SDL_GL_SwapWindow(window); 
	SDL_Delay(15);
	}
	TextureArray::clean();
	framebuffer.clean(); 
	shadowframebuffer.clean(); 
	skybox.clean(); 
	renderer->destroy();
	lights->clean();
	shadowShader->clean();
	delete shadowShader; 
	delete shader;
	delete terrain_shader; 


	
}