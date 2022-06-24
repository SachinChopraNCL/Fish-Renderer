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
		void update(int key, double delta_time, double mouse_yaw, double mouse_pitch);
	private:

		glm::vec3& update_camera_position(int key, double delta_time);
		glm::vec3& updata_camera_forward_direction(double mouse_yaw, double mouse_pitch);
		glm::mat4 _view_matrix = glm::mat4(1.0f);
		glm::vec3 _camera_position = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _camera_front = glm::vec3(0.0f, 0.0f, 1.0f);
		glm::vec3 _camera_right = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _camera_up = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 _world_up = glm::vec3(0.0f, 0.0f, 0.0f);
		
		float _camera_speed = 25.0f; 
	};
}


#endif 