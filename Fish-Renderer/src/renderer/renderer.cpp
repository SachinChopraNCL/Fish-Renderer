#include <renderer.h>

#include "render_object.cpp"

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
	load_vertex_arrays();
}

void renderer::load_vertex_arrays() {
	vertex_attribute_layout vertex_layout = vertex_attribute_layout(0, 3, 0, GL_FLOAT, false);
	vertex_attribute_layout colour_layout = vertex_attribute_layout(1, 4, 0, GL_FLOAT, false);
	vertex_attribute_layout texture_layout = vertex_attribute_layout(2, 2, 0, GL_FLOAT, false);


	std::shared_ptr<vertex_array> default_vertex_array = std::make_shared<vertex_array>();
	default_vertex_array->add_layout(data_type::POSITION, vertex_layout);
	default_vertex_array->add_layout(data_type::COLOUR, colour_layout);
	default_vertex_array->add_layout(data_type::TEXTURE, texture_layout);

	_vertex_arrays.push_back(default_vertex_array);
}

void renderer::add_object(std::vector<float>& verticies, std::vector<float>& colours, std::vector<int>& indicies, std::vector<float>& texture_coordinates, const std::string& texture_name) {
	std::shared_ptr<render_object> new_object = std::make_shared<render_object>(_vertex_arrays[0], _shaders[0], texture_name);
	new_object->add_vertex_buffer<float>(data_type::POSITION, 0, GL_ARRAY_BUFFER, verticies, GL_STATIC_DRAW);
	new_object->add_vertex_buffer<float>(data_type::COLOUR, 0, GL_ARRAY_BUFFER, colours, GL_STATIC_DRAW);
	new_object->add_vertex_buffer<float>(data_type::TEXTURE, 0, GL_ARRAY_BUFFER, texture_coordinates, GL_STATIC_DRAW);
	new_object->add_vertex_buffer<int>(data_type::INDEX, 0, GL_ELEMENT_ARRAY_BUFFER, indicies, GL_STATIC_DRAW);
	_render_objects.push_back(new_object);
}

void renderer::draw() {
	_shaders[0].get()->set_uniform<int>("input_texture", 0);
	while (!glfwWindowShouldClose(_window.get())) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		for (auto& render_object : _render_objects) {
			render_object.get()->use_textures();
			render_object.get()->use_shader();
			render_object.get()->bind_vertex_array();
			render_object.get()->draw();
			render_object.get()->unbind_vertex_array();
		}
		glfwSwapBuffers(_window.get());
		glfwPollEvents();
	}
}