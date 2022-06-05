#ifndef SHADER_LOADER_H 
#define SHADER_LOADER_H 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

namespace fish {
	enum class load_type {
		SHADER = 0, 
		TEXTURE = 1,
	};

	typedef std::map<std::string, std::string> asset_map;
	class asset_loader {
	public:
		static const std::string load_asset_from_path(const std::string& file_name, load_type target);
	private:
		static void load_shader(asset_map& shader_map, const std::string& target_path, const std::string& file_name); 
		static void load_texture(asset_map& texture_map, const std::string& target_path, const std::string& file_name);
		static std::vector<asset_map> _asset_maps;
		static std::vector<std::string> _local_paths;
	};
}

#endif 