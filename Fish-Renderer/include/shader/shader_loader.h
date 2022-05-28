#ifndef SHADER_LOADER_H 
#define SHADER_LOADER_H 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

namespace fish {
	class shader_loader {
	public: 
		static std::string load_shader_from_path(const std::string& shader_name);
	private: 
		static const std::string _local_shader_path; 
		static std::map<std::string, std::string> _shader_map;

	};
}

#endif 