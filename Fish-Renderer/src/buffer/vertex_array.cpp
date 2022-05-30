#include <vertex_array.h>
#include <algorithm>
#include <iostream>
using namespace fish; 

vertex_array::vertex_array() { 
	glGenVertexArrays(1, &_id);
	_data_layouts = {}; 
}

void vertex_array::bind() {
	glBindVertexArray(_id);
}

void vertex_array::unbind() {
	glBindVertexArray(0);
}

void vertex_array::add_layout(data_type layout_type, vertex_attribute_layout data_layout) {
	if (location_used(data_layout)) {
		return; 
	}
	
	if (!_data_layouts.insert(std::make_pair(layout_type, data_layout)).second) {
		std::cout << "Layout type is already in use!";
		return;
	}

	bind();
	glEnableVertexAttribArray(data_layout._location);
	glVertexAttribFormat(data_layout._location, data_layout._size, data_layout._type, data_layout._normalised, data_layout._offset);
	glVertexAttribBinding(data_layout._location, _buffer_index++);
	unbind();
}

void vertex_array::delete_layout(data_type layout_type) {
	std::map<data_type, vertex_attribute_layout>::iterator it; 
	it = _data_layouts.find(layout_type);
	_data_layouts.erase(it);
}

bool vertex_array::location_used(vertex_attribute_layout& data_layout) {
	unsigned int location = data_layout._location;
	if (std::find(_locations.begin(), _locations.end(), location) == _locations.end() && _locations.size() > 0) {
		std::cout << "Location is already being used!" << std::endl;
		return true;
	}
	_locations.push_back(location); 
	return false;
}