#ifndef ASSET_LOADER_H 
#define ASSET_LOADER_H 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <memory>

namespace fish {
	template <class t> 
	using asset_map = std::map<std::string, t>;
	class asset_loader {
	public:
		static std::string _local_path;
	};
}

#endif 