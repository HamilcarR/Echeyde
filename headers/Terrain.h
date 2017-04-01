#pragma once
#include "Mesh.h"
class TerrainGenerator{
public:
	/*async methods */
	static geometry_data generateTerrain(const char* heightmap);
	static geometry_data generateTerrain(unsigned int size);


	
private:
	static float ** location_array; 
	static unsigned short size; 

	/*generate a flat terrain*/
	static geometry_data generate(unsigned int size);
	/*using heightmap to generate terrain heights*/
	static geometry_data generate(const char* file_heightmap);
};
class Terrain : public Mesh
{
public:
	Terrain();
	Terrain(geometry_data &data, std::shared_ptr<Material> &material, bool isdisplayed);
	virtual ~Terrain();


private:
	

protected:

};

