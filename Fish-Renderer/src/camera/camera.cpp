#include <camera.h>

using namespace fish; 


void camera::update() {
	_camera_right = glm::normalize(glm::cross(_camera_front, _world_up));
	_camera_up = glm::normalize(glm::cross(_camera_front, _camera_right));
	_view_matrix = glm::lookAt(_camera_position, _camera_position + _camera_front, _camera_up);
}