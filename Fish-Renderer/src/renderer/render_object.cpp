#include <render_object.h>

using namespace fish; 

render_object::render_object(const std::weak_ptr<vertex_array>& vertex_array, const std::string& model_path = "") : _bound_vertex_array(vertex_array){
}

void render_object::draw() {
}
