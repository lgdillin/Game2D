#version 450

in vec4 v_out_color; // maybe dont need this 
in vec2 v_out_texCoords;

out vec4 f_out_color;

uniform sampler2D u_diffuseTexture;
uniform vec2 u_resolution;

void main() {
	f_out_color = texture(u_diffuseTexture, v_out_texCoords);
}