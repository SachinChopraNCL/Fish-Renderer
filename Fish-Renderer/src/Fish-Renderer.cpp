
#include <Fish-Renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <shader/shader.h>
#include <buffer/vertex_array.h>
#include <buffer/buffer.h>
#include <renderer/render_object.h> 
#include <renderer/renderer.h>


using namespace fish; 

int main()
{
	std::vector<float> vert = { 
	  0.5f,  0.5f, 0.0f,  // top right
	  0.5f, -0.5f, 0.0f,  // bottom right
	  -0.5f, -0.5f, 0.0f,  // bottom left
	  -0.5f,  0.5f, 0.0f   // top left 
	};
	
	std::vector<float> col = {
	1.0f, 0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,1.0f,
	
	};

	std::vector<float> tex_coords = {
	1.0f, 1.0f,
	1.0f, 0.0f,
	0.0f, 0.0f,
	0.0f, 1.0f
	};

	std::vector<int> indicies = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
	};

	renderer r = renderer("default_config.txt");
	auto obj = r.add_object<render_object>(false, vert, col, indicies, tex_coords, "brick_texture.jpg");
	obj->_transform_component.translate(glm::vec3(0.5, 0, 0));

	auto obj2 = r.add_object<render_object>(false, vert, col, indicies, tex_coords, "brick_texture.jpg");
	obj2->_transform_component.translate(glm::vec3(-0.5, 0.5, 0));

	r.draw();



	return 0;
}
