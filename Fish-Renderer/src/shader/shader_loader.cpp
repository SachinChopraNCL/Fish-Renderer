#include <shader_loader.h>


using namespace fish; 

const std::string shader_loader::_local_shader_path = "..\\..\\..\\..\\..\\..\\Fish\\Fish-Renderer\\res\\shaders\\";
std::map<std::string, std::string> shader_loader::_shader_map = {};

const std::string shader_loader::load_shader_from_path(const std::string& shader_name) {
	if (_shader_map.find(shader_name) == _shader_map.end()) {
		std::ifstream shader_file;
		std::stringstream shader_stream;
		shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try {
			shader_file.open(_local_shader_path + shader_name);
			shader_stream << shader_file.rdbuf();
			shader_file.close();
		}
		catch (std::ifstream::failure e) {
			std::cout << "failed to load shader";
			// to-do logging
		}
		_shader_map.insert({ shader_name, shader_stream.str() });
	}
	

	std::string shader_code = _shader_map[shader_name];
	
	std::cout << shader_name + " loaded!" << std::endl;
	std::cout << shader_code << std::endl;
	std::cout << "----------------------------------------------------------------" << std::endl;
	return shader_code;
}