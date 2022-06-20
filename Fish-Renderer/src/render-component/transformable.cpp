#include <transformable.h>

using namespace fish; 

void transformable::translate(const glm::vec3& translation) {
	if (_is_static_object) { return; }
	_model_matrix = glm::translate(_model_matrix, translation); 
}

void transformable::rotate(float angle_in_radians, const glm::vec3& rotation_axis) {
	if (_is_static_object) { return; }
	_model_matrix = glm::rotate(_model_matrix, angle_in_radians, rotation_axis); 
}

void transformable::scale(const glm::vec3& scale) {
	if (_is_static_object) { return; }
	_model_matrix = glm::scale(_model_matrix, scale);
}


