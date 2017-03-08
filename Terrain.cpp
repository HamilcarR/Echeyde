#include "Terrain.h"
#include <SOIL\SOIL.h>
#include <SDL\SDL_image.h>




/*TODO : create a 2D array with vertex data on it*/






struct image_data{
	unsigned char* image; 
	unsigned int size; 
};
const float MAX_TERRAIN_HEIGHT = 50.f;
const int MAX_COLOR = 256 * 256 * 256; 

static float compute_height(const unsigned int x, const unsigned int y,const image_data image ){
	if (x < 0 || x >= image.size || y < 0 || y >= image.size)
		return 0.f;
	float pixel_value = float(image.image[x*image.size + y]); 
	float total = MAX_TERRAIN_HEIGHT * (pixel_value / 256.f) * 2 - 1;
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


geometry_data TerrainGenerator::generateTerrain(const char* file_heightmap){
	int w = 0, h = 0 , chan = 0 ; 
	unsigned char* img_data = SOIL_load_image(file_heightmap, &w, &h, 0 , SOIL_LOAD_L);
	
	assert(img_data != nullptr); 
	assert(w == h); 
	unsigned size = w; 
	geometry_data terrain;
	image_data im;
	im.image = img_data; 
	im.size = w;
	for (unsigned int width = 0; width < size; width++){
		for (unsigned int height = 0; height < size; height++){
			terrain.vertex.push_back((float)height);
			float hh = compute_height(width, height,im);
			
			terrain.vertex.push_back(hh);
			terrain.vertex.push_back((float)width);
			if (width < size - 1 && height < size - 1){
				/*first triangle indices*/
				terrain.indices.push_back(width*size + height);
				terrain.indices.push_back(width*size + height + 1);
				terrain.indices.push_back((width + 1)*size + height);
				/*second triangle indices*/
				terrain.indices.push_back((width + 1)*size + height + 1);
				terrain.indices.push_back((width + 1)*size + height);
				terrain.indices.push_back(width*size + height + 1);
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
	return terrain;
}







geometry_data TerrainGenerator::generateTerrain(unsigned int size){

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

Terrain::Terrain(geometry_data &geom, std::shared_ptr<Material>& material, bool isDisplayed)
	:Mesh(geom,material,isDisplayed) 

{



}
Terrain::~Terrain()
{
}
