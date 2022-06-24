#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H 

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <renderer.h>

namespace fish {
	class input_handler {
	public: 
		input_handler() = default; 
		input_handler(std::shared_ptr<GLFWwindow>& window): _window(window) {
			if (auto window = _window.lock()) {
				glfwSetKeyCallback(window.get(), key_callback);
				glfwSetCursorPosCallback(window.get(), mouse_callback);
			}
			_key_pressed = 0;
		}
		input_handler(input_handler const& copy) = delete; 

		inline int get_key_pressed() {
			int key = _key_pressed;
			_key_pressed = 0; 
			return key;
		}

		inline double get_mouse_pitch() {
			return _mouse_pitch;
		}

		inline double get_mouse_yaw() {
			return _mouse_yaw; 
		}

	private: 
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

			if (action == GLFW_PRESS || action == GLFW_REPEAT) {
				_key_pressed = key;
			}
		}

		static void mouse_callback(GLFWwindow* window, double x_position, double y_position) {
			if (_first_input) {
				last_x_position = x_position;
				last_y_position = y_position;
				_first_input = false; 
			}
			float x_offset = x_position - last_x_position;
			float y_offset = y_position - last_y_position;
			last_x_position = x_position;
			last_y_position = y_position;

			x_offset *= 0.1f; 
			y_offset *= 0.1f; 

			_mouse_yaw += x_offset;
			_mouse_pitch += y_offset; 

			if (_mouse_pitch > 89.0f) { _mouse_pitch = 89.0f; }
			if (_mouse_pitch < -89.0f) { _mouse_pitch = -89.0f; }
		}

		std::weak_ptr<GLFWwindow> _window;
		inline static int _key_pressed;
		inline static double _mouse_yaw; 
		inline static double _mouse_pitch; 
		inline static double last_x_position = 0;
		inline static double last_y_position = 0;
		inline static bool _first_input = true; 

	};
}

#endif