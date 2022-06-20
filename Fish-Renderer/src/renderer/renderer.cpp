#include <renderer.h>

using namespace fish; 

const std::string _local_config_path = "..\\..\\..\\..\\..\\..\\Fish\\Fish-Renderer\\res\\config\\";

void renderer::load_config(const std::string& config_file_name) {
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
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD" << std::endl;
		return;
	}
	glViewport(0, 0, _width, _height);
	_shaders.push_back(std::make_shared<shader>());
}

void renderer::draw() {
	while (!glfwWindowShouldClose(_window.get())) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto& render_object : _render_objects) {
			auto render_object_pointer = render_object.get();
			render_object_pointer->_transform_component.translate(glm::vec3(0.001f, 0, 0));
			render_object_pointer->use_textures();
			render_object_pointer->use_shader();
			const std::string& mm = "model_matrix";
			render_object_pointer->get_shader().lock()->set_uniform<glm::mat4>(mm, render_object.get()->_transform_component.get_model_matrix());
			render_object_pointer->bind_vertex_array();
			render_object_pointer->draw();
			render_object_pointer->unbind_vertex_array();
		}
		glfwSwapBuffers(_window.get());
		glfwPollEvents();
	}
}