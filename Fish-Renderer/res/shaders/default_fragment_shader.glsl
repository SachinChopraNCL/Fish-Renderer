#version 460 core 

in vec4 fragment_colour; 
in vec2 output_texture_coordinate; 

uniform sampler2D input_texture; 

void main() { 
	gl_FragColor = texture(input_texture, output_texture_coordinate);
}