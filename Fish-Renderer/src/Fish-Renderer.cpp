
#include <Fish-Renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/renderer.h>


using namespace fish; 

int main()
{
	
	renderer r = renderer("default_config.txt", renderer_type::PERSPECTIVE);
	auto obj = r.add_object<render_object>(false, "brick_texture.jpg");

	r.draw();



	return 0;
}
