#ifndef	VERTEX_ARRAY_H
#define	VERTEX_ARRAY_H 

#include <glad/glad.h>

namespace fish {
	class vertex_array {
	public:
		vertex_array();
		bind();
		unbind();
	private:
		unsigned int _id
	};
}

#endif 
