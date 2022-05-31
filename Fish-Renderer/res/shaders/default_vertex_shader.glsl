#version 460 core 

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour; 

out vec4 frag_colour; 
void main() { 
	gl_Position = vec4(position, 1); 
	frag_colour = colour;  
}