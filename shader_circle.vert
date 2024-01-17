#version 450

layout (location = 0) in vec3 in_vertexPosition;
layout (location = 1) in vec3 in_vertexColor;
layout (location = 2) in vec2 in_texCoords;

out vec2 v_texCoords;
out vec4 v_color;

uniform mat4 u_projection;
uniform mat4 u_model;
uniform mat4 u_view;

void main() {
	
	v_texCoords = in_texCoords;
	v_color = vec4(in_vertexColor, 1.0);

	gl_Position = u_projection * u_view * u_model 
		* vec4(in_vertexPosition, 1.0);
}