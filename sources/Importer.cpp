#include "../headers/Importer.h"
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
const int UV_CHANNEL = 0x0;

namespace Echeyde {

	namespace FILEIO {



		static std::string load_texture(aiTextureType tex , unsigned int index,const aiMaterial* material) {
			aiString path;
			aiReturn status = material->GetTexture(tex, index, &path, 0, 0, 0, 0, 0);
			if (status == AI_SUCCESS)
			{
				std::string full_path = RESSOURCES_LOCATION + path.data;
				return full_path;
			}
			else
				std::cout << "problem loading texture : " << path.data << std::endl;
			return "";
		}

/**********************************************************************************************************************************************/

		static textures_data get_texture_data(const aiMaterial* material , const aiScene* scene,unsigned int mesh_index) {
			textures_data tex_data;
			for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++) {
					std::string	path = load_texture(aiTextureType_DIFFUSE, i, material);
					tex_data.diffuse=(path);

			}
			for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_HEIGHT); i++) {
				
					std::string	path = load_texture(aiTextureType_HEIGHT, i, material);
					tex_data.normal = (path);
				
			}
			for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_OPACITY); i++) {
			
				
					std::string	path = load_texture(aiTextureType_OPACITY, i, material);
					tex_data.opacity = (path);
				
			}
			for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_UNKNOWN); i++) {
				
				
					std::string	path = load_texture(aiTextureType_UNKNOWN, i, material);
					tex_data.optional = (path);
				
			}
			return tex_data;
		}


/**********************************************************************************************************************************************/

		static object_data get_mesh_geometry(const aiScene* scene,unsigned int mesh_index) {
			object_data mesh;
			aiVector3t<float>* vert = (scene->mMeshes[mesh_index])->mVertices;
			aiVector3t<float>* normales = (scene->mMeshes[mesh_index])->mNormals;
			aiVector3t<float>* tangents = (scene->mMeshes[mesh_index])->mTangents;
			aiVector3t<float>* bitangents = (scene->mMeshes[mesh_index])->mBitangents;
			aiVector3t<float>* textures = (scene->mMeshes[mesh_index])->mTextureCoords[UV_CHANNEL];
			aiFace *index = (scene->mMeshes[mesh_index])->mFaces;

			for (unsigned int i = 0; i < scene->mMeshes[mesh_index]->mNumVertices; i++) {
				mesh.data.vertex.push_back(vert[i].x);
				mesh.data.vertex.push_back(vert[i].y);
				mesh.data.vertex.push_back(vert[i].z);
				mesh.data.color.push_back(vert[i].x);
				mesh.data.color.push_back(vert[i].y);
				mesh.data.color.push_back(vert[i].z);
				mesh.data.normal.push_back(normales[i].x);
				mesh.data.normal.push_back(normales[i].y);
				mesh.data.normal.push_back(normales[i].z);
				mesh.data.tangent.push_back(tangents[i].x);
				mesh.data.tangent.push_back(tangents[i].y);
				mesh.data.tangent.push_back(tangents[i].z);
				mesh.data.bitangent.push_back(bitangents[i].x);
				mesh.data.bitangent.push_back(bitangents[i].y);
				mesh.data.bitangent.push_back(bitangents[i].z);
				mesh.data.texture.push_back(textures[i].x);
				mesh.data.texture.push_back(textures[i].y);
			}
			for (unsigned int i = 0; i < scene->mMeshes[mesh_index]->mNumFaces; i++) {
				mesh.data.indices.push_back(static_cast<unsigned short>(index[i].mIndices[0]));
				mesh.data.indices.push_back(static_cast<unsigned short>(index[i].mIndices[1]));
				mesh.data.indices.push_back(static_cast<unsigned short>(index[i].mIndices[2]));
			}
			return mesh;
		}


/**********************************************************************************************************************************************/
	
		
		
		
		static material_data get_material_data(const aiMaterial *material, const aiScene* scene, unsigned int mesh_index, bool transparency) {
			material_data material_dat; 
			textures_data tex_data = get_texture_data(material, scene, mesh_index);
			material_dat.textures = tex_data;
			float shine=1 , strength = 1;
			material->Get(AI_MATKEY_SHININESS_STRENGTH, strength);
			material->Get(AI_MATKEY_SHININESS, shine);
			shine = shine / 4; 
			material_dat.specular_exponent = (shine<140) ? shine : 140;
			material_dat.specular_strength = strength; 
			material_dat.transparency = transparency;
			return material_dat; 
		}

		
		
		
		
/**********************************************************************************************************************************************/

		std::vector<object_data> Importer::load_model(std::string& filename, bool transparency) {
			std::vector<object_data> data;
			Assimp::Importer importer;
			const aiScene *scene = importer.ReadFile(RESSOURCES_LOCATION+filename, aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_JoinIdenticalVertices);
			if (scene == nullptr) {
				throw Importer_Error(importer,filename);
				return data; 
			}
			const aiMaterial* material;
			unsigned int mesh_number = scene->mNumMeshes; 
			for (size_t mesh_index = 0; mesh_index < mesh_number; mesh_index++)
			{
				object_data mesh = get_mesh_geometry(scene, mesh_index);
				material = scene->mMaterials[scene->mMeshes[mesh_index]->mMaterialIndex];
				mesh.material = get_material_data(material, scene, mesh_index,transparency);
				data.push_back(mesh); 

				
			}
			

			return data;
		}
	
	
/**********************************************************************************************************************************************/
		material_data Importer::getMaterial(std::string &file , bool transparency){
			std::vector<object_data> object;
			try{
				object = load_model(file,transparency);
			}
			catch (const File_not_found &e) {
				std::cout << e.what() << std::endl;
			}
			catch (const MaterialException &e) {
				std::cout << e.what() << std::endl;
			}
			catch (const Importer_Error &e) {
				std::cout << e.what() << std::endl;
			}
			
			assert(object.size() == 1); 
			return object[0].material; 



		}














	}
}
