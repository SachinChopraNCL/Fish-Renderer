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
			glfwSetKeyCallback(_window.lock().get(), key_callback);
			_key_pressed = 0;
		}
		input_handler(input_handler const& copy) = delete; 

		inline int get_key_pressed() {
			int key = _key_pressed;
			_key_pressed = 0; 
			return key;
		}

	private: 
		std::weak_ptr<GLFWwindow> _window;
		inline static int _key_pressed;

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			
			std::cout << "here";
			if (action == GLFW_PRESS || action == GLFW_REPEAT) {
				_key_pressed = key;
			}
		}

	};
}

#endif