#ifndef TEXTURE_LOADER_H 
#define TEXTURE_LOADER_H

#include <glad/glad.h>
#include <asset_loader.h>

namespace fish {
	class texture_loader : public asset_loader {
	public:
		static const GLuint& load_texture_from_path(const std::string& file_name);
	private:
		static asset_map<GLuint> _texture_map;
	};
}

#endif TEXTURE_LOADER_H