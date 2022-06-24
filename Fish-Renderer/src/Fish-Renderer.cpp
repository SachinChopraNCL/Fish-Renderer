
#include <Fish-Renderer.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <renderer/renderer.h>


using namespace fish; 

int main()
{
	
	renderer r = renderer("default_config.txt", renderer_type::PERSPECTIVE);
	auto obj = r.add_object<render_object>(false, "brick_texture.jpg");
	obj.get()->_transform_component.rotate(glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	r.draw();
	return 0;
}
