#include <texture_loader.h>
#include <stb_image.h>

using namespace fish;

asset_map<GLuint> texture_loader::_texture_map = {};

const GLuint& texture_loader::load_texture_from_path(const std::string& file_name) {
	GLuint tex_id; 
	if (_texture_map.find(file_name) == _texture_map.end()) {
		glGenTextures(1, &tex_id);
		glBindTexture(GL_TEXTURE_2D, tex_id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		int width, height, nr_channels;
		std::string path = asset_loader::_local_path + "\\textures\\" + file_name; 
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nr_channels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		_texture_map.insert({ file_name, tex_id });
		stbi_image_free(data);
		std::cout << file_name + " loaded!" << std::endl;
	}
	return _texture_map[file_name];
}