#pragma once
#include "Mesh.h"

class Renderer
{
public:
	Renderer* getInstance(); 
	void* destroy(); 
	void addMeshData(std::shared_ptr<Mesh> &mesh);

private:
	Renderer();
	virtual ~Renderer();





};

