#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace fish {
	class transformable {
	public:
		transformable(bool is_static_object) : _is_static_object(is_static_object){}
		void translate(const glm::vec3& translation); 
		void rotate(float angle_in_radians, const glm::vec3& rotation_axis);
		void scale(const glm::vec3& scale);
		inline bool is_static() {
			return _is_static_object; 
		}
		inline const glm::mat4& get_model_matrix() {
			return _model_matrix; 
		}
	private: 
		glm::mat4 _model_matrix = glm::mat4(1.0f);
		bool _is_static_object; 
	};
}




#endif 