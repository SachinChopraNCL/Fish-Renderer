#include <asset_loader.h>


using namespace fish; 

const std::string _local_shader_path = "..\\..\\..\\..\\..\\..\\Fish\\Fish-Renderer\\res\\shaders\\";
const std::string _local_texture_path = "..\\..\\..\\..\\..\\..\\Fish\\Fish-Renderer\\res\\textures\\";

static asset_map _shader_map = {};
static asset_map _texture_map = {};


std::vector<asset_map> asset_loader::_asset_maps = { _shader_map, _texture_map };
std::vector<std::string> asset_loader::_local_paths = {_local_shader_path, _local_texture_path };

const std::string asset_loader::load_asset_from_path(const std::string& file_name, load_type target) {
	int target_index = static_cast<int>(target);
	asset_map& target_map = _asset_maps[target_index];
	std::string& target_path = _local_paths[target_index];
	if (target_map.find(file_name) == target_map.end()) {
		switch (target) {
			case(load_type::SHADER): 
				load_shader(target_map, target_path, file_name);
				break;
			case(load_type::TEXTURE):
				load_texture(target_map, target_path, file_name);
				break; 
		}

	}

	std::string asset_string = target_map[file_name];
	
	if (target == load_type::SHADER) {
		std::cout << file_name + " loaded!" << std::endl;
		std::cout << asset_string << std::endl;
		std::cout << "----------------------------------------------------------------" << std::endl;
	}

	return asset_string;
}

void asset_loader::load_shader(asset_map& shader_map, const std::string& target_path, const std::string& file_name) {
	std::ifstream file;
	std::stringstream file_stream;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		file.open(target_path + file_name);
		file_stream << file.rdbuf();
		file.close();
	}
	catch (std::ifstream::failure e) {
		std::cout << "failed to load shader";
		// to-do logging
	}
	shader_map.insert({ file_name, file_stream.str() });
}

void asset_loader::load_texture(asset_map& texture_map, const std::string& target_path, const std::string& file_name) {

}

