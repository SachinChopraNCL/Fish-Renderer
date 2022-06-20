#version 460 core 

in VERTEX_SHADER_OUTPUT {
	vec4 fragment_colour; 
	vec2 output_texture_coordinate; 
} fragment_shader_input; 

uniform sampler2D input_texture; 

void main() { 
	gl_FragColor = texture(input_texture, fragment_shader_input.output_texture_coordinate);
}