#include <model_loader.h>

using namespace fish; 

asset_map<std::vector<mesh_data>> model_loader::_mesh_map = {};
std::vector<mesh_data> model_loader::_model_data = {};
Assimp::Importer model_loader::_importer = Assimp::Importer();


const std::vector<mesh_data> model_loader::get_model_from_path(const std::string& file_name) {
	if (_mesh_map.find(file_name) == _mesh_map.end()) {
		_model_data.clear();
		const std::string file_path = asset_loader::_local_path + "\models\\" + file_name;
		const aiScene* scene = _importer.ReadFile(file_path, aiProcess_Triangulate | aiProcess_FlipUVs);
		
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "Assimp error! :: " << _importer.GetErrorString() << std::endl;
			return {};
		}
		process_node(scene->mRootNode, scene);
		_mesh_map[file_name] = _model_data;
	}

	auto meshes = _mesh_map[file_name];

	return meshes;
}

void model_loader::process_node(aiNode* node, const aiScene* scene) {
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		process_mesh(mesh, scene);
	}

	for (int i = 0; i < node->mNumChildren; i++) {
		process_node(node->mChildren[i], scene); 
	}
}

void model_loader::process_mesh(aiMesh* mesh, const aiScene* scene) {
	mesh_data new_mesh_data; 
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		new_mesh_data._vertices.push_back(mesh->mVertices[i].x);
		new_mesh_data._vertices.push_back(mesh->mVertices[i].y);
		new_mesh_data._vertices.push_back(mesh->mVertices[i].z);

		if (auto texture_coordinate = mesh->mTextureCoords[0]) {
			new_mesh_data._texture_coordinates.push_back(texture_coordinate[i].x);
			new_mesh_data._texture_coordinates.push_back(texture_coordinate[i].y);
		}
		else {
			new_mesh_data._texture_coordinates.push_back(0);
			new_mesh_data._texture_coordinates.push_back(0);
		}
	}

	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		for (int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++) {

		}
	}

	for (int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) {
			new_mesh_data._indices.push_back(face.mIndices[j]);
		}
	}
	_model_data.push_back(new_mesh_data);
}