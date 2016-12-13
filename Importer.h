#pragma once
#include "Constants.h"
#include "File_not_found.h"
#include "MaterialException.h"

namespace Echeyde {
	namespace FILEIO {
		class Importer
		{

		private:
			static vertex_data get_data_vertices(std::fstream* obj);

			static material_data get_data_materials(std::fstream* mtl);

			static std::string get_material_name(std::fstream &buf);


		public:
			
			static object_data load_OBJ(std::string filename);

		};

	}
}
