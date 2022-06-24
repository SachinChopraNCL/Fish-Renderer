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
	_window = glfw_window_pointer(glfwCreateWindow(_width, _height, _window_title.c_str(), NULL, NULL), destroy_glfw_window());
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
	glfwSetInputMode(_window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glViewport(0, 0, _width, _height);
}

void renderer::draw() {
	while (!glfwWindowShouldClose(_window.get())) {
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		_timer.update(); 
		int key = _input_handler.get_key_pressed();
		_renderer_camera.update(key, _timer.get_delta_time(), _input_handler.get_mouse_yaw(), _input_handler.get_mouse_pitch());
		for (auto& render_object : _render_objects) {
			auto render_object_pointer = render_object.get();
			render_object_pointer->setup();
			render_object_pointer->update(_projection_matrix, _renderer_camera.get_view_matrix());
			render_object_pointer->draw();
		}
		glfwSwapBuffers(_window.get());
		glfwPollEvents();
	}
}