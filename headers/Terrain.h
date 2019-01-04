#ifndef TERRAIN_H
#define TERRAIN_H
#include "Mesh.h"
#include "GameObject.h"
struct terrain_data_struct{
	geometry_data terrain_data; 
	std::vector<std::vector<float>> collision_map; 

};

class TerrainGenerator{
public:
	/*async methods */
	static terrain_data_struct generateTerrain(const char* heightmap);
	static geometry_data generateTerrain(unsigned int size);


	
private:
	static float ** location_array; 
	static unsigned short size; 

	/*generate a flat terrain*/
	static geometry_data generate(unsigned int size);
	/*using heightmap to generate terrain heights*/
	static terrain_data_struct generate(const char* file_heightmap);
};
class Terrain : public GameObject
{
public:
	Terrain();
	Terrain(std::vector<object_data> list_mesh, Shader* s, bool displayed, bool isStatic , std::vector<std::vector<float>> collision);
	virtual ~Terrain();

	float getHeightCollisionMap(float x, float y);

private:


protected:

	std::vector<std::vector<float>> collision_map; 
};

#endif
