#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vector>
#include <memory>
#include <glad/glad.h>
#include <vertex_array.h>

namespace fish {
	template <typename t>
	class buffer {
	public:
		static GLuint create_buffer(data_type data_type, GLenum binding_point, std::vector<t>& buffer_data, GLenum data_intent) {
			GLuint _id;
			glGenBuffers(1, &_id);
			glBindBuffer(binding_point, _id);
			glBufferData(binding_point, buffer_data.size() * sizeof(t), &buffer_data.front(), data_intent);
			glBindBuffer(binding_point, 0);
			return _id; 
		}
	};
}

#endif