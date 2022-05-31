#include <render_object.h>
#include <iostream>
using namespace fish; 

render_object::render_object(std::weak_ptr<vertex_array>& vertex_array, const std::string& model_name) : _bound_vertex_array(vertex_array), _model_name(model_name) {
	if (vertex_array.expired()) {
		return;
	}
	_bound_vertex_array = vertex_array;
}

void render_object::set_vertex_array(std::weak_ptr<vertex_array>& vertex_array) {
	if (vertex_array.expired()) {
		return; 
	}
	_bound_vertex_array = vertex_array;

	//todo remap vertex buffers if possible
}

void render_object::add_vertex_buffer(data_type type, GLintptr offset, GLenum binding_point, std::vector<float>& buffer_data, GLenum data_intent) {
	if (_bound_vertex_array.expired()) {
		std::cout << "Need a Vertex_Array bound before buffering data!" << std::endl; 
		return; 
	}

	std::shared_ptr<vertex_array> raw_vertex_array = _bound_vertex_array.lock();
	std::vector<data_type> vertex_array_layouts = raw_vertex_array->get_data_layouts();

	if (type != vertex_array_layouts[_buffer_index]) {
		std::cout << "Mismatch of buffered data type and the vertex array layout!" << std::endl;
	}

	buffer<float> new_buffer = buffer<float>(type, binding_point, buffer_data, data_intent); 
	_buffers.push_back(new_buffer);
	_buffer_ids.push_back(new_buffer.get_id());
	_offsets.push_back(offset);
	_strides.push_back(data_helpers::get_stride_from_type(type));
	_buffer_index++; 
}


void render_object::draw() {
	if (_bound_vertex_array.expired()) {
		return;
	}
	glBindVertexBuffers(0, 1, &_buffer_ids[0], &_offsets[0], &_strides[0]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}
