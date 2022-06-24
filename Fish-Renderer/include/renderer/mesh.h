#ifndef MESH_H
#define MESH_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <buffer.h> 

#include <vector>
#include <map>
#include <variant>
#include <texture_loader.h>


namespace fish {

	typedef std::map<data_type, std::variant<std::vector<float>, std::vector<int>>> mesh_data_map;
	
	enum texture_type {
		SPECULAR, 
		DIFFUSE,
	};

	struct texture {
		GLuint _id; 
		texture_type _type; 
	};

	class mesh {
	public: 
		mesh(std::vector<float>& positions, std::vector<float>& normals, std::vector<float>& texture_coordinates
			, std::vector<int>& indicies, std::vector<float>& colours, std::vector<std::string> _texture_name);

		void load_data(std::vector<data_type>& layouts);
		void draw();

	private: 
		template <typename t>
		inline void add_vertex_buffer(data_type type, GLintptr offset, GLenum binding_point, std::vector<t>& buffer_data, GLenum data_intent) {
			if (type == data_type::INDEX) {
				_index_buffer = buffer<t>::create_buffer(type, binding_point, buffer_data, data_intent);
				_number_of_indices = buffer_data.size();
				return;
			}

			if (type == data_type::POSITION) {
				_number_of_verticies = buffer_data.size();
			}
			_buffers.push_back(buffer<t>::create_buffer(type, binding_point, buffer_data, data_intent));
			_offsets.push_back(offset);
			_strides.push_back(data_helpers::get_stride_from_type(type));
		}
		void use_textures();
		unsigned int _number_of_verticies = 0;
		unsigned int _number_of_indices = 0;

		std::vector<GLuint> _buffers; 
		std::vector<GLintptr> _offsets; 
		std::vector<GLsizei> _strides; 
	
		GLuint _index_buffer; 
		std::vector<GLuint> _mesh_textures = {};
		GLenum _draw_target = GL_TRIANGLES;

		mesh_data_map _object_data;

	};
}

#endif MESH_H