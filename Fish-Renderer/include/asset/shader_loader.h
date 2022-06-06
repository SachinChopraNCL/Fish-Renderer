#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <asset_loader.h>

namespace fish {
	class shader_loader : public asset_loader {
	public: 
		static const std::string load_shader_from_path(const std::string& file_name);
	private: 
		static asset_map _shader_map; 
	};
}








#endif


