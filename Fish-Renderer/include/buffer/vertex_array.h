#ifndef	VERTEX_ARRAY_H
#define	VERTEX_ARRAY_H 

#include <glad/glad.h>
#include <vector>

namespace fish {

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
		vertex_array(std::vector<vertex_attribute_layout> data_layouts);
		void set_layouts(); 
		void bind();
		void unbind();
		void add_layout(vertex_attribute_layout data_layout);
		bool location_used (vertex_attribute_layout& data_layout); 
	private:
		unsigned int _id;
		std::vector<vertex_attribute_layout> _data_layouts; 
		std::vector<int> _locations;  
	};
}

#endif 
