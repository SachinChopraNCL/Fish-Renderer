#include <render_object.h>
#include <texture_loader.h>
#include <iostream>
using namespace fish; 

render_object::render_object(const std::string& texture_name, bool is_static_object, const std::string& model_name) : _transform_component(is_static_object), _model_name(model_name) {
	_object_texture.push_back(texture_loader::load_texture_from_path(texture_name));
	_attributes = generate_attribute_layout();
	_shader_target = generate_shader_target();

	// temp 
	_object_data[data_type::POSITION] = _vertices;
	_object_data[data_type::COLOUR] = _colours;
	_object_data[data_type::TEXTURE] = _texture_coordinates;
	_object_data[data_type::INDEX] = _indicies;

}


void render_object::set_vertex_array(std::shared_ptr<vertex_array>& vertex_array) {
	_bound_vertex_array = vertex_array;
	auto layouts = _bound_vertex_array.lock().get()->get_data_layouts();
	for (auto& layout : layouts) {
		auto layout_data = std::get<std::vector<float>>(_object_data[layout]);
		if (layout_data.size() <= 0) {
			std::cout << "layout_data empty!" << std::endl;
			continue;
		}
		add_vertex_buffer<float>(layout, 0, GL_ARRAY_BUFFER, layout_data, GL_STATIC_DRAW);
	}
	if (_object_data.find(data_type::INDEX) != _object_data.end()) {
		add_vertex_buffer<int>(data_type::INDEX, 0, GL_ELEMENT_ARRAY_BUFFER, std::get<std::vector<int>>(_object_data[data_type::INDEX]), GL_STATIC_DRAW);
	}
}

object_shader_target render_object::generate_shader_target() {
	return object_shader_target("default", "default_vertex_shader.glsl", "default_fragment_shader.glsl");
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

void render_object::setup() {
	use_textures();
	use_shader();
}

void render_object::update(const glm::mat4& projection_matrix, const glm::mat4& view_matrix) {
	// move this to renderer
	get_shader().lock()->set_uniform<glm::mat4>("view_matrix", view_matrix);
	get_shader().lock()->set_uniform<glm::mat4>("projection_matrix", projection_matrix);
	get_shader().lock()->set_uniform<glm::mat4>("model_matrix", _transform_component.get_model_matrix());
}

void render_object::draw() {
	bind_vertex_array();
	if (_bound_vertex_array.expired()) {
		return;
	}
	glBindVertexBuffers(0, _buffers.size(), &_buffers[0], &_offsets[0], &_strides[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
	glDrawElements(_draw_target, _number_of_indices, GL_UNSIGNED_INT, 0);
	unbind_vertex_array();
}
