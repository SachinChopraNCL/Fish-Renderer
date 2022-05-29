#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vector>
#include <glad/glad.h>

namespace fish {
	template <typename t>
	class vertex_buffer {
	public:
		vertex_buffer(std::vector<t>& buffer_data, GLenum data_intent) {
			glGenBuffers(1, &_id);
			glBindBuffer(GL_ARRAY_BUFFER, _id);
			glBufferData(GL_ARRAY_BUFFER, sizeof(buffer_data), &buffer_data[0], data_intent);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		vertex_buffer(vertex_buffer& rhs) = delete; 
		GLuint _id;
	};
}

#endif