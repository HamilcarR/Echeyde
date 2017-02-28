#pragma once
#include "Mesh.h"
class TerrainGenerator{
public:
	static geometry_data generateTerrain(unsigned int size);



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

