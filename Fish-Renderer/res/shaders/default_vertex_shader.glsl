#version 460 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour; 
layout(location = 2) in vec2 input_texture_coordinate;



out vec4 fragment_colour; 
out vec2 output_texture_coordinate;

void main() { 
	gl_Position = vec4(position, 1); 
	fragment_colour = colour;  
	output_texture_coordinate = input_texture_coordinate;
}