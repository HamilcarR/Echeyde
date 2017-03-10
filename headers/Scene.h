#pragma once
#include "View.h"
#include "Mesh.h"
namespace Echeyde {
	class Scene
	{
	public:
		Scene();
		virtual ~Scene();
		

	private:
		std::vector<Mesh> scene; 
	};


}
