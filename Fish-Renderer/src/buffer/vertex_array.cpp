#include <vertex_array.h>
#include <algorithm>
#include <iostream>
using namespace fish; 

vertex_array::vertex_array(std::vector<vertex_attribute_layout> data_layouts):_data_layouts(data_layouts) {
	glGenVertexArrays(1, &_id);
	set_layouts();
}

void vertex_array::set_layouts() {
	bind();
	for (vertex_attribute_layout& data_layout : _data_layouts) {
		if (location_used(data_layout)) {
			continue; 
		}
		glEnableVertexAttribArray(data_layout._location);
		glVertexAttribFormat(data_layout._location, data_layout._size, data_layout._type, data_layout._normalised, data_layout._offset);
		glVertexAttribBinding(data_layout._location, 0);
	}
	unbind();
}

void vertex_array::bind() {
	glBindVertexArray(_id);
}

void vertex_array::unbind() {
	glBindVertexArray(0);
}

void vertex_array::add_layout(vertex_attribute_layout data_layout) {
	if (location_used(data_layout)) {
		return; 
	}
	_data_layouts.push_back(data_layout);
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