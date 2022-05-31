#ifndef RENDER_OBJECT_H 
#define RENDER_OBJECT_H

#include <vertex_array.h>
#include <data_type.h>
#include <buffer.h> 
#include <memory>
#include <map>
#include <string>

namespace fish {
	class render_object {
	public: 
		render_object(std::weak_ptr<vertex_array>& vertex_array, const std::string& model_name = "");
		void set_vertex_array(std::weak_ptr<vertex_array>& vertex_array);
		void add_vertex_buffer(data_type type, GLintptr offset, GLenum binding_point, std::vector<float>& buffer_data, GLenum data_intent);
		void draw(); 
	private: 
		std::weak_ptr<vertex_array> _bound_vertex_array; 
		std::vector<GLuint> _buffers;
		std::vector<GLintptr> _offsets;
		std::vector<GLsizei> _strides; 
		unsigned int _buffer_index = 0; 
		std::string _model_name; 
		static const std::string _local_model_path; 
	};
}

#endif