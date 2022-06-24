#include <camera.h>
#include <iostream>
#include <math.h>      

using namespace fish; 

void camera::update(int key, double delta_time, double mouse_yaw, double mouse_pitch) {
	_camera_front = updata_camera_forward_direction(mouse_yaw, mouse_pitch);
	_camera_position += update_camera_position(key, delta_time);
	_camera_right = glm::normalize(glm::cross(_camera_front, _world_up));
	_camera_up = glm::normalize(glm::cross(_camera_front, _camera_right));
	_view_matrix = glm::lookAt(_camera_position, _camera_position + _camera_front, _camera_up);
}

glm::vec3& camera::update_camera_position(int key, double delta_time) {
	glm::vec movement_vector = glm::vec3(0.0f, 0.0f, 0.0f);
	switch (key) {
		case('W'): {
			movement_vector = glm::vec3(0.0f, 0.0f, _camera_speed * delta_time);
			break;
		}
		case('S'): {
			movement_vector = glm::vec3(0.0f, 0.0f, -_camera_speed * delta_time);
			break;
		}
		case('A'): {
			movement_vector = glm::vec3(-_camera_speed * delta_time, 0.0f, 0.0f);
			break;
		}
		case('D'): {
			movement_vector = glm::vec3(_camera_speed * delta_time, 0.0f, 0.0f);
			break;
		}
	}
	return movement_vector; 
}

glm::vec3& camera::updata_camera_forward_direction(double mouse_yaw, double mouse_pitch) {
	glm::vec3 forward_direction = glm::vec3(0.0f, 0.0f, 1.0f);
	forward_direction.x = cos(glm::radians(mouse_yaw)) * cos(glm::radians(mouse_pitch));
	forward_direction.y = sin(glm::radians(mouse_pitch));
	forward_direction = glm::normalize(forward_direction);
	return forward_direction;
}