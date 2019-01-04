#ifndef IMPORTER_H
#define IMPORTER_H
#include "Constants.h"
#include "File_not_found.h"
#include "MaterialException.h"
#include "Importer_Error.h"
namespace Echeyde {
	namespace FILEIO {
		struct stream_load;
		class Importer
		{
		public:
			static std::vector<object_data> load_model(std::string file, bool transparency);
			static material_data getMaterial(std::string file , bool transparency); 
		};

	}
}
#endif
