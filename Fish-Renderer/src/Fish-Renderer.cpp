
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
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);
	if (!window) {
		std::cout << "Failed to create Window!" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	//initialise glad 
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialise GLAD" << std::endl; 
		return -1;
	}
	std::vector<float> vert = { 
		// first triangle
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f,  0.5f, 0.0f,  // top left 
		// second triangle
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left
	
	};
	
	std::vector<float> col = {
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f, 
	0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 0.0f, 1.0f
	
	};


	shader s;

	renderer r = renderer("default_config.txt");

	//vertex_attribute_layout layout = vertex_attribute_layout(0, 3, 0, GL_FLOAT, false);
	//vertex_attribute_layout layout1 = vertex_attribute_layout(1, 4, 0, GL_FLOAT, false);


	//std::shared_ptr va1 = std::make_shared<vertex_array>();

	//std::weak_ptr va2(va1);

	//va1->add_layout(data_type::POSITION, layout);
	//va1->add_layout(data_type::COLOUR, layout1); 


	//render_object obj(va2);
	//obj.add_vertex_buffer(data_type::POSITION, 0, GL_ARRAY_BUFFER, vert, GL_STATIC_DRAW);
	//obj.add_vertex_buffer(data_type::COLOUR, 0, GL_ARRAY_BUFFER, col, GL_STATIC_DRAW);

	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);

	//glViewport(0, 0, 800, 600);

	//while (!glfwWindowShouldClose(window)) {

	//	glClearColor(0, 0, 0, 0);
	//	glClear(GL_COLOR_BUFFER_BIT);
	//	s.use();
	//	va1->bind();
	//	obj.draw();
	//	va1->unbind();
	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}
	return 0;
}
