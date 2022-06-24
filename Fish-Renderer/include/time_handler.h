#ifndef TIME_HANDLER_H
#define TIME_HANDLER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace fish {
	class time_handler {
	public: 
		time_handler() = default; 
		time_handler(const time_handler& copy) = delete; 
		time_handler& operator=(const time_handler& copy) = delete; 
		void update() {
			double current_frame_time = glfwGetTime();
			_delta_time = current_frame_time - _last_frame_time;
			_last_frame_time = current_frame_time; 
		}
		const double get_delta_time() { 
			return _delta_time;
		}
	private: 
		double _last_frame_time = 0;
		double _delta_time = 0; 

	};
} 






#endif