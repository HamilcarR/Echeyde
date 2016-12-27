#pragma once
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
			static std::vector<object_data> load_model(std::string& file);
		};

	}
}
