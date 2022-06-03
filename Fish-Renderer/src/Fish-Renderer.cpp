
#include <Fish-Renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec4.hpp>
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
	0.0f, 0.5f, 0.5f, 1.0f,
	0.0f, 1.0f, 0.5f, 1.0f, 
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f
	
	};

	std::vector<int> indicies = {  // note that we start from 0!
	0, 1, 3,   // first triangle
	1, 2, 3    // second triangle
	};

	renderer r = renderer("default_config.txt");
	r.add_object(vert, col, indicies);
	r.draw();

	return 0;
}
