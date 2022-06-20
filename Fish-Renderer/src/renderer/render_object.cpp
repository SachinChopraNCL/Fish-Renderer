#include <render_object.h>
#include <texture_loader.h>
#include <iostream>
using namespace fish; 

render_object::render_object(std::shared_ptr<shader>& shader, const std::string& texture_name, bool is_static_object, const std::string& model_name) : _bound_shader(shader), _transform_component(is_static_object), _model_name(model_name) {
	_object_texture.push_back(texture_loader::load_texture_from_path(texture_name));
	_attributes = generate_attribute_layout();
}

void render_object::set_vertex_array(std::shared_ptr<vertex_array>& vertex_array) {
	_bound_vertex_array = vertex_array; 
}

object_attribute_layout render_object::generate_attribute_layout() {
	std::vector<vertex_attribute_layout> layouts;
	layouts.push_back(vertex_attribute_layout(data_type::POSITION, 0, 3, 0, GL_FLOAT, false));
	layouts.push_back(vertex_attribute_layout(data_type::COLOUR, 1, 4, 0, GL_FLOAT, false));
	layouts.push_back(vertex_attribute_layout(data_type::TEXTURE, 2, 2, 0, GL_FLOAT, false));
	return object_attribute_layout("default", layouts);
}

void render_object::set_shader(std::shared_ptr<shader>& new_shader) {
	_bound_shader = new_shader; 
}

void render_object::draw() {
	if (_bound_vertex_array.expired()) {
		return;
	}
	glBindVertexBuffers(0, _buffers.size(), &_buffers[0], &_offsets[0], &_strides[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
	glDrawElements(_draw_target, _number_of_indices, GL_UNSIGNED_INT, 0);
}
