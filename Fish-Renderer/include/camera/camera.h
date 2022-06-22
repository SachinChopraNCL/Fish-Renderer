#ifndef CAMERA_H 
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fish {
	class camera {
	public: 
		camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3 up = glm::vec3(0.0f, 0.0f, 0.0f)) : _camera_position(position), _world_up(up) {}
		camera(camera& copy) = delete; 
		[[nodiscard]] inline const glm::mat4& get_view_matrix() {
			return _view_matrix; 
		}
		void update(); 
	private:
		glm::mat4 _view_matrix = glm::mat4(1.0f);
		glm::vec3 _camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _camera_front = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 _camera_right = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _camera_up = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _world_up = glm::vec3(0.0f, 0.0f, 0.0f);
	};
}


#endif 