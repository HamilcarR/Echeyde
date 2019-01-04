#include "../headers/Terrain.h"
#include <SOIL/SOIL.h>
#include <SDL2/SDL_image.h>






terrain_data_struct TerrainGenerator::generateTerrain(const char* heightmap){
	
	terrain_data_struct(*ptr)(const char*) = &TerrainGenerator::generate;
	auto f = std::async(std::launch::async,
		[&ptr , heightmap]{
		return ptr((HEIGHTMAPS_LOCATION + std::string(heightmap)).c_str());
	}
	);
	return f.get();

}
geometry_data TerrainGenerator::generateTerrain(unsigned int size){
	geometry_data(*ptr)(unsigned int) = &TerrainGenerator::generate;
	auto f = std::async(std::launch::async,
		[&ptr, size]{
		return ptr(size);
	}
	);
	return f.get();
}




/*TODO : create a 2D array with vertex data on it*/

float **TerrainGenerator::location_array = nullptr;
unsigned short TerrainGenerator::size = 0; 



struct image_data{
	unsigned char* image; 
	unsigned int size; 
};
const float MAX_TERRAIN_HEIGHT = 50.f;

static float compute_height(const unsigned int x, const unsigned int y,const image_data image ){
	if (x < 0 || x >= image.size || y < 0 || y >= image.size)
		return 0.f;
	float pixel_value = float(image.image[x*image.size + y]); 
	float total = MAX_TERRAIN_HEIGHT * ((pixel_value / 256.f) * 2 - 1);
	return total;
}

static glm::vec3 compute_normals(int offset, unsigned int PosX, unsigned int PosY, const image_data image){
	float right = compute_height(PosX + offset, PosY , image);
	float left = compute_height(PosX - offset, PosY, image);
	float up = compute_height(PosX, PosY + offset, image); 
	float down = compute_height(PosX, PosY - offset, image); 

	float X = left - right;
	float Y = 2.0; 
	float Z = down - up;
	return normalize(glm::vec3(X, Y, Z)); 
}


terrain_data_struct TerrainGenerator::generate(const char* file_heightmap){
	int w = 0, h = 0 , chan = 0 ; 
	unsigned char* img_data = SOIL_load_image(file_heightmap, &w, &h, 0 , SOIL_LOAD_L);	
	assert(img_data != nullptr); 
	assert(w == h); 
	unsigned size = w; 
	terrain_data_struct terrain_data; 
	terrain_data.collision_map.resize(size); 
	for (unsigned int i = 0; i < size; i++)
		terrain_data.collision_map[i].resize(size); 

	geometry_data terrain;
	image_data im;
	im.image = img_data; 
	im.size = w;
	for (unsigned int width = 0; width < size; width++){
		for (unsigned int height = 0; height < size; height++){
			terrain.vertex.push_back((float)height);
			float hh = compute_height(width, height,im);
			terrain_data.collision_map[width][height] = hh;
			terrain.vertex.push_back(hh);
			terrain.vertex.push_back((float)width);
			if (width < size - 1 && height < size - 1){
				/*first triangle indices*/
				terrain.indices.push_back((width + 1)*size + height);
				terrain.indices.push_back(width*size + height + 1);
				terrain.indices.push_back(width*size + height);
				/*second triangle indices*/
				terrain.indices.push_back(width*size + height + 1);
				terrain.indices.push_back((width + 1)*size + height);
				terrain.indices.push_back((width + 1)*size + height + 1);

			}

			terrain.texture.push_back(height / (float)size);
			terrain.texture.push_back(width / (float)size);

			glm::vec3 normal = compute_normals(1, height, width, im); 
			terrain.normal.push_back(normal.x);
			terrain.normal.push_back(normal.y);
			terrain.normal.push_back(normal.z);

			terrain.bitangent.push_back(0);
			terrain.bitangent.push_back(1);
			terrain.bitangent.push_back(0);

			terrain.color.push_back(0);
			terrain.color.push_back(0);
			terrain.color.push_back(0);

			terrain.tangent.push_back(0);
			terrain.tangent.push_back(1);
			terrain.tangent.push_back(0);

		}
	}

	SOIL_free_image_data(img_data);
	terrain_data.terrain_data = terrain; 
	return terrain_data;
}







geometry_data TerrainGenerator::generate(unsigned int size){

	geometry_data terrain; 
	

	/*generating vertices and textures coordinates*/
	
	for (unsigned int width = 0; width < size; width ++){
		for (unsigned int height = 0; height < size; height++){
			terrain.vertex.push_back((float)height); 
			terrain.vertex.push_back(0.f);
			terrain.vertex.push_back((float)width);
			if (width < size - 1 && height < size - 1){
				/*first triangle indices*/
				terrain.indices.push_back(width*size + height);
				terrain.indices.push_back(width*size + height + 1);
				terrain.indices.push_back((width + 1)*size + height);
				/*second triangle indices*/
				terrain.indices.push_back(width*size + height + 1);
				terrain.indices.push_back((width + 1)*size + height);
				terrain.indices.push_back((width + 1)*size + height + 1);
			}
			terrain.texture.push_back(height / (float)size);
			terrain.texture.push_back(width / (float)size);

			terrain.normal.push_back(0);
			terrain.normal.push_back(1);
			terrain.normal.push_back(0);

			terrain.bitangent.push_back(0);
			terrain.bitangent.push_back(1);
			terrain.bitangent.push_back(0);

			terrain.color.push_back(0);
			terrain.color.push_back(0);
			terrain.color.push_back(0);

			terrain.tangent.push_back(0);
			terrain.tangent.push_back(1);
			terrain.tangent.push_back(0);

		}
	}
	
	return terrain; 
}


Terrain::Terrain()
{
}

Terrain::Terrain(std::vector<object_data> list_mesh, Shader* s, bool displayed, bool isStatic , std::vector<std::vector<float>> collision)
	:GameObject(list_mesh , s , displayed , isStatic) 

{
	collision_map = collision;


}
Terrain::~Terrain()
{
}


struct POINT_LERP_ {
	/*Height values in the collision map*/
	float V00; 
	float V01; 
	float V10;
	float V11;
	/*Coordinates at corner*/
	float Xsup; 
	float Xinf;
	float Ysup;
	float Yinf;
	/*Coordinates of the lerped point*/
	float x; 
	float y; 

};


static float interpolate2D(const POINT_LERP_  &point){
	/*we interpolate on the X axis*/
	float valueY1 = ((point.Xsup - point.x) / (point.Xsup - point.Xinf))*point.V00 + ((point.x - point.Xinf) / (point.Xsup - point.Xinf))* point.V10; 
	float valueY2 = ((point.Xsup - point.x) / (point.Xsup - point.Xinf))*point.V01 + ((point.x - point.Xinf) / (point.Xsup - point.Xinf))* point.V11; 
	/*on the Y axis */
	float result = ((point.Ysup - point.y) / (point.Ysup - point.Yinf)) * valueY1 + ((point.y - point.Yinf) / (point.Ysup - point.Yinf)) * valueY2;

	return result; 

}






float Terrain::getHeightCollisionMap(float x ,float y){
	

	

	if (x < collision_map.size() && y < collision_map.size() && x >= 0 && y >= 0){
		if (floor(x) == x){

		}
		
		if (floor(y) == y){

		}
		float val; 
		POINT_LERP_ point;
		float Xinf = floor(x); Xinf = (Xinf < 0.) ? 0.f : (Xinf >= collision_map.size()-1.) ? collision_map.size() - 2. : Xinf; 
		float Yinf = floor(y); Yinf = (Yinf < 0.) ? 0.f : (Yinf >= collision_map.size()-1.) ? collision_map.size() - 2. : Yinf; 
		float Xsup = ceil(x); Xsup = (Xsup < 1.) ? 1.f : (Xsup >= collision_map.size()) ? collision_map.size() - 1. : Xsup; 
		float Ysup = ceil(y); Ysup = (Ysup < 1.) ? 1.f : (Ysup >= collision_map.size()) ? collision_map.size() - 1. : Ysup; 
		
		float  height0_0 = collision_map[Xinf][Yinf]; 
		float  height1_0 = collision_map[Xsup][Yinf]; 
		float  height0_1 = collision_map[Xinf][Ysup];
		float  height1_1 = collision_map[Xsup][Ysup]; 

		point.V00 = height0_0; 
		point.V01 = height0_1;
		point.V10 = height1_0;
		point.V11 = height1_1;
		point.Xinf = Xinf;
		point.Xsup = Xsup;
		point.Yinf = Yinf;
		point.Ysup = Ysup; 
		point.x = x; 
		point.y = y; 


			
		return  interpolate2D(point ); 
	}

	// bilinear interpolation

	/*	
			return collision_map[x][y];
		else
			return 0.f; */


	return 0.;
	}
