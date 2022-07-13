#ifndef MODEL_LOADER_H
#define MODEL_LOADER_H

#include <asset_loader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h> 
#include <assimp/postprocess.h>

namespace fish {
	struct mesh_data {
		std::vector<float> _vertices;
		std::vector<float> _texture_coordinates; 
		std::vector<float> _colours; 
		std::vector<int> _indices;
		std::vector<std::string> _texture_names; 
	};
	class model_loader : public asset_loader {
	public:
		static const std::vector<mesh_data> get_model_from_path(const std::string& file_name);
	private:
		static std::vector<mesh_data> _model_data; 
		static void process_node(aiNode* node, const aiScene* scene);
		static void process_mesh(aiMesh* mesh, const aiScene* scene);
		static asset_map<std::vector<mesh_data>> _mesh_map; 
		static Assimp::Importer _importer; 
	};
}
	


#endif MODEL_LOADER_H