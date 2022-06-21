#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <vector>
#include <map>

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
		template <class t>
		inline std::shared_ptr<render_object> add_object(bool is_static_object, std::vector<float>& verticies, std::vector<float>& colours, std::vector<int>& indicies, std::vector<float>& texture_coordinates, const std::string& texture_name) {
			std::shared_ptr<render_object> new_object = std::make_shared<t>(texture_name, is_static_object);
			// resolve shader
			auto shader_target = new_object->get_shader_target(); 
			std::string& shader_name = shader_target._name;
			if (_shader_map.find(shader_name) == _shader_map.end()) {
				std::shared_ptr<shader> new_shader = std::make_shared<shader>(shader_target._vertex_target, shader_target._fragment_target);
				_shader_map[shader_name] = new_shader;
			}
			new_object->set_shader(_shader_map[shader_name]);
			// resolve attribute layout for intended shader 
			auto attribute_loader = new_object->get_object_layout();
			std::string& vertex_array_name = attribute_loader._name;
			if (_vertex_array_map.find(vertex_array_name) == _vertex_array_map.end()) {
				std::shared_ptr<vertex_array> new_vertex_array = std::make_shared<vertex_array>();
				for (vertex_attribute_layout& layout : attribute_loader._layouts) {
					new_vertex_array->add_layout(layout);
				}
				_vertex_array_map[vertex_array_name] = new_vertex_array;
			}
			new_object->set_vertex_array(_vertex_array_map[vertex_array_name]);
			_render_objects.push_back(new_object);
			return new_object;
		}
	private: 
		void load_config(const std::string& config_file_name);
		void initialise();
	
		glfw_window_pointer _window = nullptr;
		std::string _window_title = "default";

		std::map<std::string, std::shared_ptr<vertex_array>> _vertex_array_map = {};
		std::map<std::string, std::shared_ptr<shader>> _shader_map = {};
		std::vector<std::shared_ptr<render_object>> _render_objects = {};

		std::string _scene_name = "";
		
		unsigned int _width = 600, _height = 600; 
		unsigned int _major_version = 3, _minor_version = 3;
	};
}






#endif