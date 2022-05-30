#ifndef	VERTEX_ARRAY_H
#define	VERTEX_ARRAY_H 

#include <glad/glad.h>
#include <vector>
#include <map>

namespace fish {

	enum data_type {
		POSITION,
		COLOUR,
		NORMAL
	};

	struct vertex_attribute_layout {
		vertex_attribute_layout(unsigned int location, unsigned int size,  unsigned int offset, GLenum type = GL_FLOAT, bool normalised = false) : _location(location), _offset(offset), _size(size), _type(type), _normalised(normalised) {}
		unsigned int _location; 
		unsigned int _size; 
		unsigned int _offset;
		bool _normalised; 
		GLenum _type;
	};
	
	class vertex_array {
	public:
		vertex_array();
		void bind();
		void unbind();
		void add_layout(data_type layout_type, vertex_attribute_layout data_layout);
		bool location_used (vertex_attribute_layout& data_layout); 
		const std::vector<data_type>& get_data_layouts(){
			return _data_layouts; 
		}

	private:
		GLuint _id;
		unsigned int _buffer_index = 0; 
		std::vector<data_type> _data_layouts; 
		std::vector<int> _locations;  
	};
}

#endif 
