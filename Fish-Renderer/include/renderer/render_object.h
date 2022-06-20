#ifndef RENDER_OBJECT_H 
#define RENDER_OBJECT_H

#include <vertex_array.h>
#include <data_type.h>
#include <buffer.h> 
#include <shader.h>
#include <transformable.h>

#include <vector>
#include <memory>
#include <map>
#include <string>

namespace fish {
	struct object_attribute_layout {
	public:
		object_attribute_layout() = default; 
		object_attribute_layout(const std::string& name, std::vector<vertex_attribute_layout> layouts): _name(name), _layouts(layouts) { }
		std::string _name;
		std::vector<vertex_attribute_layout> _layouts; 
	};
	class render_object {
	public: 
		render_object(std::shared_ptr<shader>& shader, const std::string& texture_name, bool is_static_object, const std::string& model_name = "");
		void set_vertex_array(std::shared_ptr<vertex_array>& vertex_array);
		void set_shader(std::shared_ptr<shader>& new_shader);
		template <typename t>
		inline void add_vertex_buffer(data_type type, GLintptr offset, GLenum binding_point, std::vector<t>& buffer_data, GLenum data_intent) {
			if (_bound_vertex_array.expired()) {
				std::cout << "Need a Vertex_Array bound before buffering data!" << std::endl;
				return;
			}

			if (type == data_type::INDEX) {
				_index_buffer = buffer<t>::create_buffer(type, binding_point, buffer_data, data_intent);
				_number_of_indices = buffer_data.size();
				return;
			}

			std::shared_ptr<vertex_array> raw_vertex_array = _bound_vertex_array.lock();
			std::vector<data_type> vertex_array_layouts = raw_vertex_array->get_data_layouts();

			if (type != vertex_array_layouts[_buffer_index++]) {
				std::cout << "Mismatch of buffered data type and the vertex array layout!" << std::endl;
			}

			if (type == data_type::POSITION) {
				_number_of_verticies = buffer_data.size();
			}

			_buffers.push_back(buffer<t>::create_buffer(type, binding_point, buffer_data, data_intent));
			_offsets.push_back(offset);
			_strides.push_back(data_helpers::get_stride_from_type(type));
		}
		void draw(); 
		void change_draw_target(GLenum new_target) {
			_draw_target = new_target;
		}
		inline std::weak_ptr<shader> get_shader() {
			return _bound_shader;
		}
		inline void bind_vertex_array() {
			auto vertex_array = _bound_vertex_array.lock();
			if (!vertex_array) {
				std::cout << "Vertex array is no longer valid!"; 
				return;
			}
			vertex_array->bind();
		}
		inline void unbind_vertex_array() {
			auto vertex_array = _bound_vertex_array.lock();
			if (!vertex_array) {
				std::cout << "Vertex array is no longer valid!";
				return;
			}
			vertex_array->unbind();
		}
		inline void use_shader() {
			auto shader = _bound_shader.lock();
			if (!shader) {
				std::cout << "Shader is no longer valid!";
				return;
			}
			shader->use();
		}

		inline void use_textures() {
			int i = 0; 
			for (GLuint& _texture : _object_texture) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, _texture);
				i++;
			}
		}

		inline object_attribute_layout& get_object_layout() {
			return _attributes; 
		}

		transformable _transform_component;

	private: 

		virtual object_attribute_layout generate_attribute_layout(); 

		object_attribute_layout _attributes;

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
		
		std::vector<GLuint> _object_texture; 

		std::string _model_name;
		static const std::string _local_model_path; 

	};
}

#endif