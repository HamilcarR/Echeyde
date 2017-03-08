#pragma once
#include "Mesh.h"
class TerrainGenerator{
public:
	/*generate a flat terrain*/
	static geometry_data generateTerrain(unsigned int size);
	/*using heightmap to generate terrain heights*/
	static geometry_data generateTerrain(const char* file_heightmap);


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

