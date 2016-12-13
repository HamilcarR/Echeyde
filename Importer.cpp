#include "Importer.h"

namespace Echeyde {
	namespace FILEIO {
		 vertex_data Importer::get_data_vertices(std::fstream *obj) {
			vertex_data data;
			




			obj->close();
			return data;

		}

		 material_data Importer::get_data_materials(std::fstream *mtl) {
			material_data data;



			mtl->close();
			return data;
		 }

		 std::string Importer::get_material_name(std::fstream &obj) {
			 std::string buf;
			 while (std::getline(obj, buf)) {
				 char* tok = strtok(((char*)buf.c_str()), " ");
				 while (tok != NULL) {
					 if (std::string(tok).compare("mtllib") == 0) {
						 tok = strtok(NULL, " ");
						 if (tok != NULL) {
							 obj.close();
							 return std::string(tok);
						 }
					}
					 tok = strtok(NULL, " ");
				 }
			 }
			 obj.close(); 
			 throw  MaterialException() ;
			 return std::string(); 
		}



		 object_data Importer::load_OBJ(std::string filename) {
			object_data data;
			std::fstream obj;
			std::fstream mtl;
			std::string file = filename+".obj";
			std::string mat_name = RESSOURCES_LOCATION;
			file = RESSOURCES_LOCATION + file;
			obj.open(file.c_str(), std::ios::in);

			if (!obj.is_open()) {
				throw File_not_found(file);
				return data;
			}
			mat_name += get_material_name(obj); 
			obj.open(file.c_str(),std::ios::in);
			mtl.open(mat_name.c_str(), std::ios::in);
			if (!mtl.is_open()) {
				throw File_not_found(mat_name);
				return data; 
			}
			auto t_obj = std::async(std::launch::async, get_data_vertices, &obj); 
			auto t_mtl = std::async(std::launch::async, get_data_materials, &mtl); 

			data.data = t_obj.get(); 
			data.material = t_mtl.get(); 










			return data;
		 }
	
	
	
	
	
	
	
	
	
	
	
	
	}
}
