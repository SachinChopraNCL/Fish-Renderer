#ifndef SHADER_H 
#define SHADER_H 

#include <glad/glad.h>
#include <shader_loader.h>
#include <string>


namespace fish {
	class shader {
	public:
		shader(); 
		shader(const std::string& vertex_shader_file, const std::string& fragment_shader_file);
		~shader();

		void set_vertex_shader(const std::string& vertex_shader_file);
		void set_fragment_shader(const std::string& fragment_shader_file);

		// todo - maybe remove?
		void recompile_shader(); 

		void use(); 
		
		template <typename t> 
		void set_uniform(const std::string& uniform_name, t value); 



		bool _is_shader_valid = true;
	
	private:
		void compile_shader();
		
		void check_compile(unsigned int shader); 
		void check_linking(); 

		std::string _cached_vertex_string = "";
		std::string _cached_fragment_string = ""; 

		std::string _vertex_shader_code; 
		std::string _fragment_shader_code; 
		
		const std::string _default_vertex_shader = "default_vertex_shader.glsl";
		const std::string _default_fragment_shader = "default_fragment_shader.glsl";

		GLuint _id; 
	};
}

#endif