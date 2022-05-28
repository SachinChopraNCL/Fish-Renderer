#ifndef SHADER_H 
#define SHADER_H 

#include <glad/glad.h>
#include <shader_loader.h>
#include <string>


namespace fish {
	class shader {
	public:
		shader(); 
		shader(std::string vertex_shader_file, std::string fragment_shader_file);
		~shader();

		void set_vertex_shader(std::string vertex_shader_file);
		void set_fragment_shader(std::string);
		void recompile_shader(); 

		void use(); 
	
	private:
		void compile_shader();

		std::string _cached_vertex_string = "";
		std::string _cached_fragment_string = ""; 

		std::string _vertex_shader_code; 
		std::string _fragment_shader_code; 
		
		const std::string _default_vertex_shader = "default_vertex_shader.glsl";
		const std::string _default_fragment_shader = "default_fragment_shader.glsl";

		unsigned int _id; 
	};
}

#endif