#ifndef ASSET_LOADER_H 
#define ASSET_LOADER_H 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>

namespace fish {
	typedef std::map<std::string, std::string> asset_map;
	class asset_loader {
	public:
		static std::string _local_path;
	};
}

#endif 