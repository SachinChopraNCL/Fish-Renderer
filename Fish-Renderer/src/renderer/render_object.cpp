#include <render_object.h>
#include <iostream>
using namespace fish; 

render_object::render_object(std::shared_ptr<vertex_array>& vertex_array, std::shared_ptr<shader>& shader, const std::string& model_name) : _bound_vertex_array(vertex_array), _bound_shader(shader),  _model_name(model_name) {
	if (!vertex_array.get()) {
		return;
	}
}


void render_object::set_shader(std::shared_ptr<shader>& new_shader) {
	_bound_shader = new_shader; 
}

template <typename t>
void render_object::add_vertex_buffer(data_type type, GLintptr offset, GLenum binding_point, std::vector<t>& buffer_data, GLenum data_intent) {
	if (_bound_vertex_array.expired()) {
		std::cout << "Need a Vertex_Array bound before buffering data!" << std::endl; 
		return; 
	}

	if (type == data_type::INDEX) {
		_index_buffer = buffer<t>::create_buffer(type, binding_point, buffer_data, data_intent);
		_number_of_indices = buffer_data.size();
		return;
	}

	std::shared_ptr<vertex_array> raw_vertex_array = _bound_vertex_array.lock();
	std::vector<data_type> vertex_array_layouts = raw_vertex_array->get_data_layouts();

	if (type != vertex_array_layouts[_buffer_index++]) {
		std::cout << "Mismatch of buffered data type and the vertex array layout!" << std::endl;
	}

	if (type == data_type::POSITION) {
		_number_of_verticies = buffer_data.size();
	}

	_buffers.push_back(buffer<t>::create_buffer(type, binding_point, buffer_data, data_intent));
	_offsets.push_back(offset);
	_strides.push_back(data_helpers::get_stride_from_type(type));
}

void render_object::draw() {
	if (_bound_vertex_array.expired()) {
		return;
	}
	glBindVertexBuffers(0, 2, &_buffers[0], &_offsets[0], &_strides[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
	glDrawElements(_draw_target, _number_of_indices, GL_UNSIGNED_INT, 0);
}
