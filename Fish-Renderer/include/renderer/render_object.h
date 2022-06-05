#ifndef RENDER_OBJECT_H 
#define RENDER_OBJECT_H

#include <vertex_array.h>
#include <data_type.h>
#include <buffer.h> 
#include <shader.h>

#include <memory>
#include <map>
#include <string>

namespace fish {
	class render_object {
	public: 
		render_object(std::shared_ptr<vertex_array>& vertex_array, std::shared_ptr<shader>& shader, const std::string& model_name = "");
		void set_vertex_array(std::shared_ptr<vertex_array>& vertex_array);
		void set_shader(std::shared_ptr<shader>& new_shader);
		template <typename t>
		void add_vertex_buffer(data_type type, GLintptr offset, GLenum binding_point, std::vector<t>& buffer_data, GLenum data_intent);
		void draw(); 
		void change_draw_target(GLenum new_target) {
			_draw_target = new_target;
		}
		inline void bind_vertex_array() {
			if (auto vertex_array = _bound_vertex_array.lock()) {
				vertex_array->bind();
			}
		}
		inline void unbind_vertex_array() {
			if (auto vertex_array = _bound_vertex_array.lock()) {
				vertex_array->unbind();
			}
		}
		inline void use_shader() {
			if (auto shader = _bound_shader.lock()) {
				shader->use();
			}
		}

	private: 
		std::weak_ptr<vertex_array> _bound_vertex_array; 
		std::weak_ptr<shader> _bound_shader; 

		std::vector<GLuint> _buffers;
		std::vector<GLintptr> _offsets;
		std::vector<GLsizei> _strides; 

		GLenum _draw_target = GL_TRIANGLES; 
		GLuint _index_buffer;

		unsigned int _buffer_index = 0; 
		unsigned int _number_of_verticies = 0; 
		unsigned int _number_of_indices = 0;
		
		std::string _model_name;
		static const std::string _local_model_path; 
	};
}

#endif