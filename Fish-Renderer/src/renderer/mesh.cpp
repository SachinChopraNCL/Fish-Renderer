#include <mesh.h>

using namespace fish;

mesh::mesh(std::vector<float>& positions, std::vector<float>& normals, std::vector<float>& texture_coordinates
	, std::vector<int>& indicies, std::vector<float>& colours, std::vector<std::string> _texture_name) {
	_object_data[data_type::POSITION] = positions;
	_object_data[data_type::NORMAL] = normals;
	_object_data[data_type::COLOUR] = colours;
	_object_data[data_type::TEXTURE] = texture_coordinates;
	_object_data[data_type::INDEX] = indicies;

	for (std::string& texture_name : _texture_name) {
		_mesh_textures.push_back(texture_loader::load_texture_from_path(texture_name));
	}
}

void mesh::load_data(std::vector<data_type>& layouts) {
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

void mesh::use_textures() {
	int i = 0;
	for (GLuint& _texture : _mesh_textures) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, _texture);
		i++;
	}
}

void mesh::draw() {
	glBindVertexBuffers(0, _buffers.size(), &_buffers[0], &_offsets[0], &_strides[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _index_buffer);
	glDrawElements(_draw_target, _number_of_indices, GL_UNSIGNED_INT, 0);
}