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
		render_object(std::shared_ptr<vertex_array>& vertex_array, const std::string& model_name = "");
		void set_vertex_array(std::weak_ptr<vertex_array>& vertex_array);
		template <typename t>
		void add_vertex_buffer(data_type type, GLintptr offset, GLenum binding_point, std::vector<t>& buffer_data, GLenum data_intent);
		void draw(); 
	private: 
		std::weak_ptr<vertex_array> _bound_vertex_array; 
		std::vector<GLuint> _buffers;
		std::vector<GLintptr> _offsets;
		std::vector<GLsizei> _strides; 
		GLuint _index_buffer;
		unsigned int _buffer_index = 0; 
		unsigned int _number_of_verticies = 0; 
		std::string _model_name; 
		static const std::string _local_model_path; 
	};
}

#endif