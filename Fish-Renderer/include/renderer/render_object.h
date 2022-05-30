#ifndef RENDER_OBJECT_H 
#define RENDER_OBJECT_H

#include <vertex_array.h>
#include <buffer.h> 
#include <memory>
#include <map>
#include <string>

namespace fish {
	class render_object {
	public: 
		render_object(const std::weak_ptr<vertex_array>& vertex_array,const std::string& model_path);
		void add_vertex_buffer();
		void draw(); 
	private: 
		std::weak_ptr<vertex_array> _bound_vertex_array; 
		std::map <std::string, GLuint> _vertex_buffer_map;
		static const std::string _local_model_path; 
	};
}

#endif