#version 460 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour; 
layout(location = 2) in vec2 input_texture_coordinate;


out VERTEX_SHADER_OUTPUT { 
	vec4 fragment_colour; 
	vec2 output_texture_coordinate;
} vertex_shader_output;


uniform mat4 projection_matrix; 
uniform mat4 model_matrix; 
uniform mat4 view_matrix; 

void main() { 
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1); 
	vertex_shader_output.fragment_colour = colour;  
	vertex_shader_output.output_texture_coordinate = input_texture_coordinate;
}