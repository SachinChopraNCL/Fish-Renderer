#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>

#include <fstream>
#include <sstream>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vertex_array.h>
#include <render_object.h>
#include <shader.h>

namespace fish {
	struct destroy_glfw_window {
		void operator()(GLFWwindow* ptr) {
			glfwDestroyWindow(ptr);
		}
	};

	typedef std::unique_ptr<GLFWwindow, destroy_glfw_window> glfw_window_pointer; 

	class renderer {
	public: 
		renderer(const std::string& config_file_name) { 
			load_config(config_file_name);
			initialise(); 
		}
		renderer(renderer& copy) = delete; 
		renderer& operator= (renderer const& copy) = delete; 
		void draw(); 
		void add_object(std::vector<float>& verticies, std::vector<float>& colours);
	private: 
		void load_config(const std::string& config_file_name);
		void initialise();
		void load_vertex_arrays();
	
		glfw_window_pointer _window = nullptr;
		std::string _window_title = "default";

		std::vector<std::shared_ptr<vertex_array>> _vertex_arrays = {};
		std::vector<std::shared_ptr<render_object>> _render_objects = {};
		std::vector<shader> _shaders = {}; 

		std::string _scene_name = "";
		
		unsigned int _width = 600, _height = 600; 
		unsigned int _major_version = 3, _minor_version = 3;
	};
}






#endif