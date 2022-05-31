#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <vector>
#include <vertex_array.h>
#include <glad/glad.h>

namespace fish {
	template <typename t>
	class buffer {
	public:
		buffer() = default; 
		buffer(data_type data_type, GLenum binding_point,  std::vector<t>& buffer_data, GLenum data_intent): _data_type(data_type) {
			bind_data(binding_point, buffer_data, data_intent);
		}
		void bind_data(GLenum binding_point, std::vector<t>& buffer_data, GLenum data_intent) {
			glGenBuffers(1, &_id);
			glBindBuffer(binding_point, _id);
			glBufferData(binding_point, sizeof(buffer_data), &buffer_data[0], data_intent);
			glBindBuffer(binding_point, 0);
		}
		const GLuint get_id() { return _id;  }
		const data_type get_buffer_intent() { return _data_type; }
	private:
		GLuint _id;
		data_type _data_type;
	};
}

#endif