
#include <shader_loader.h>

using namespace fish;

asset_map<std::string> shader_loader::_shader_map = {};

const std::string& shader_loader::load_shader_from_path(const std::string& file_name) {
	if (_shader_map.find(file_name) == _shader_map.end()) {
		std::ifstream file;
		std::stringstream file_stream;
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			file.open(asset_loader::_local_path + "\\shaders\\" + file_name);
			file_stream << file.rdbuf();
			file.close();
		}
		catch (std::ifstream::failure e) {
			std::cout << "failed to load shader";
			// to-do logging
		}
		_shader_map.insert({ file_name, file_stream.str() });
	}
	std::string& shader_string = _shader_map[file_name];

	std::cout << file_name + " loaded!" << std::endl;
	std::cout << shader_string << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;

	return shader_string; 
}
