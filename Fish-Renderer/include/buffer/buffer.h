#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vector>
#include <glad/glad.h>

namespace fish {
	template <typename t>
	class buffer {
	public:
		buffer() = default; 
		buffer(GLenum binding_point,  std::vector<t>& buffer_data, GLenum data_intent) {
			bind_data(binding_point, buffer_data, data_intent);
		}
		void bind_data(GLenum binding_point, std::vector<t>& buffer_data, GLenum data_intent) {
			glGenBuffers(1, &_id);
			glBindBuffer(binding_point, _id);
			glBufferData(binding_point, sizeof(buffer_data), &buffer_data[0], data_intent);
			glBindBuffer(binding_point, 0);
		}
		GLuint get_id() { return _id;  }
	private:
		GLuint _id;
	};
}

#endif