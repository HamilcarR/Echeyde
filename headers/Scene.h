#ifndef SCENE_H
#define SCENE_H
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
#endif
