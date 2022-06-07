#ifndef DATA_TYPE_H
#define DATA_TYPE_H
#include <iostream>
namespace fish {
	enum data_type {
		POSITION = 0,
		COLOUR = 1,
		NORMAL = 2,
		INDEX = 3,
		TEXTURE = 4, 
	};
	
	class data_helpers {
	public: 
		static float get_stride_from_type(data_type type) {
			switch (type) {
				case(data_type::POSITION):  
					return 3 * sizeof(float);
				case(data_type::COLOUR): 
					return 4 * sizeof(float);
				case(data_type::NORMAL):
					return 3 * sizeof(float);
				case(data_type::TEXTURE):
					return 2 * sizeof(float);
				default: 
					std::cout << "Invalid data type" << std::endl;
					break; 
			}
		}
	};
}






#endif