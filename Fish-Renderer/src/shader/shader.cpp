#include <shader.h>
#include <asset_loader.h>
#include <config.h>

using namespace fish; 


shader::shader() {
	set_vertex_shader(_default_vertex_shader);
	set_fragment_shader(_default_fragment_shader);
	compile_shader();
}

shader::shader(const std::string& vertex_shader_file, const std::string& fragment_shader_file) {
	set_vertex_shader(vertex_shader_file);
	set_fragment_shader(fragment_shader_file);
	compile_shader();
}

shader::~shader() {

}

void shader::set_vertex_shader(const std::string& vertex_shader_file) {
	if (vertex_shader_file == _cached_vertex_string) return;
	_vertex_shader_code = shader_loader::load_shader_from_path(vertex_shader_file);
	_cached_vertex_string = vertex_shader_file; 
    
}

void shader::set_fragment_shader(const std::string& fragment_shader_file) {
	if (fragment_shader_file == _cached_vertex_string) return;
	_fragment_shader_code = shader_loader::load_shader_from_path(fragment_shader_file);
	_cached_fragment_string = fragment_shader_file;
}

void shader::compile_shader() {
	unsigned int vertex_shader, fragment_shader; 
	
	const char* vertex_shader_code = _vertex_shader_code.c_str();
	const char* fragment_shader_code = _fragment_shader_code.c_str();

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &vertex_shader_code, NULL);
	glCompileShader(vertex_shader);
	check_compile(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &fragment_shader_code, NULL);
	glCompileShader(fragment_shader);
	check_compile(fragment_shader);

	_id = glCreateProgram();
	glAttachShader(_id, vertex_shader);
	glAttachShader(_id, fragment_shader);
	glLinkProgram(_id);
	check_linking();

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

}

void shader::recompile_shader() {

}

void shader::check_compile(unsigned int shader) {
	int success_flag; 
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success_flag);
	if (!success_flag) {
		_is_shader_valid = false; 
		std::cout << "Shader compilation failed!" << std::endl;
	}
}

void shader::check_linking() {
	int success_flag; 
	glGetShaderiv(_id, GL_LINK_STATUS, &success_flag);
	if(!success_flag) {
		_is_shader_valid = false;
		std::cout << "Shader linking failed!" << std::endl;
	}
}

void shader::use() {
	glUseProgram(_id);
}

template <typename t> 
void shader::set_uniform(const std::string& uniform, t value) {
	// default template assumes an int, may cause unintended effects!
	GLint location = glGetUniformLocation(_id, uniform.c_str());
	glUniform1i(location, (int)value);
}

template<> 
void shader::set_uniform<int>(const std::string& uniform, int value) {
	GLint location = glGetUniformLocation(_id, uniform.c_str());
	glUniform1i(location, (int)value);
}

template<>
void shader::set_uniform<float>(const std::string& uniform, float value) {
	GLint location = glGetUniformLocation(_id, uniform.c_str());
	glUniform1f(location, value);
}

template<>
void shader::set_uniform<bool>(const std::string& uniform, bool value) {
	GLint location = glGetUniformLocation(_id, uniform.c_str());
	glUniform1i(location, (int)value);
}

