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
}

void render_object::add_vertex_buffer(data_type type, GLenum binding_point, std::vector<float>& buffer_data, GLenum data_intent) {
	if (_bound_vertex_array.expired()) {
		std::cout << "Need a Vertex_Array bound before buffering data!" << std::endl; 
		return; 
	}

	std::shared_ptr<vertex_array> raw_vertex_array = _bound_vertex_array.lock();
	std::vector<data_type> vertex_array_layouts = raw_vertex_array->get_data_layouts();

	if (type != vertex_array_layouts[_buffer_index]) {
		std::cout << "Mismatch of buffered data type and the vertex array layout!" << std::endl;
	}

	_buffers.push_back(buffer<float> { binding_point, buffer_data, data_intent});
	_buffer_index++; 
}


void render_object::draw() {
	std::vector<GLuint> buffer_ids; 
	for (buffer<float>& buffer : _buffers) {
		buffer_ids.push_back(buffer.get_id());
	}
	GLintptr offsets[1];
	GLsizei  strides[1];
	offsets[0] = 0;
	strides[0] = 3 * sizeof(float);
	if (_bound_vertex_array.expired()) {
		return;
	}
	glBindVertexBuffers(0, 1, &buffer_ids[0], offsets, strides);
	glDrawArrays(GL_TRIANGLES, 0, 3);

}
