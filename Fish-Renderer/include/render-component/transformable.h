#ifndef TRANSFORMABLE_H
#define TRANSFORMABLE_H

#include <glm/glm.hpp>

namespace fish {
	class transformable {
	public:
		void translate(glm::vec3 translation); 
		void rotate(glm::vec3 rotate);
		const glm::mat4& get_model_matrix();
	private: 
		glm::mat4 _model_matrix = glm::mat4(1.0f);
	};
}




#endif 