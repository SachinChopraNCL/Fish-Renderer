#include <renderer.h>

using namespace fish; 

const std::string _local_config_path = "..\\..\\..\\..\\..\\..\\Fish\\Fish-Renderer\\res\\config\\";

void renderer::load_config(std::string config_file_name) {
	std::ifstream config_file; 
	std::string line;
	try {
		config_file.open(_local_config_path + config_file_name);
		
		std::getline(config_file, line);
		std::stringstream dimensions(line);
		dimensions >> _height >> _width; 

		std::getline(config_file, line);
		std::stringstream versions (line);
		versions >> _major_version >> _minor_version;

		std::getline(config_file, line);
		std::stringstream window_title(line);
		window_title >> _window_title;
	}
	catch (std::ifstream::failure e) {
		std::cout << "failed to load config" << std::endl; 
	}
}

void renderer::initialise() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _major_version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _minor_version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	_window = glfw_window_pointer(glfwCreateWindow(_width, _height, _window_title.c_str(), NULL, NULL));
	if (!_window) {
		std::cout << "Failed to create Window!" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_window.get());

}

void renderer::load_vertex_arrays() {

}