#include <render_object.h>
#include <texture_loader.h>
#include <iostream>
using namespace fish; 

render_object::render_object(bool is_static_object, const std::string& model_name) : _transform_component(is_static_object), _model_name(model_name) {
	_attributes = generate_attribute_layout();
	_shader_target = generate_shader_target();
	
	// temp
	std::vector<float> normals;
	auto all_mesh_data = model_loader::get_model_from_path(model_name);
	for (auto& mesh_data : all_mesh_data) {
		mesh m = mesh(mesh_data._vertices, normals, mesh_data._texture_coordinates, mesh_data._indices, normals, { "brick_texture.jpg" });
		_meshes.push_back(m);
	}
}


void render_object::set_vertex_array(std::shared_ptr<vertex_array>& vertex_array) {
	_bound_vertex_array = vertex_array;
	auto layouts = _bound_vertex_array.lock().get()->get_data_layouts();
	for (mesh& submesh : _meshes) {
		submesh.load_data(layouts);
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
	for (mesh& submesh : _meshes) {
		submesh.draw();
	}
	unbind_vertex_array();
}
