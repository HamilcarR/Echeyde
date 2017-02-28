#include "Terrain.h"



geometry_data TerrainGenerator::generateTerrain(unsigned int size){

	geometry_data terrain; 
	

	/*generating vertices and textures coordinates*/
	for (unsigned int width = 0; width < size; width++){
		for (unsigned int height = 0; height < size; height++){
			terrain.vertex.push_back(height); 
			terrain.vertex.push_back(0);
			terrain.vertex.push_back(width);
			

			terrain.texture.push_back((float)height / (float)size);
			terrain.texture.push_back((float)width / (float)size);

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
	/*managing indices*/
	for (unsigned int level = 0; level < size; level++){
		for (unsigned int var = 0; var < size; var++){
			/*first triangle*/
			terrain.indices.push_back(level*size + var);
			terrain.indices.push_back(level*size + var + 1);
			terrain.indices.push_back((level+1)*size + var);
			/*second triangle*/
			terrain.indices.push_back(level*size + var + 1);
			terrain.indices.push_back((level + 1)*size + var);
			terrain.indices.push_back((level + 1)*size + var + 1);


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
