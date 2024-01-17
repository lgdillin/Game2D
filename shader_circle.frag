#version 450

in vec4 v_color;

out vec4 fragColor;

uniform vec2 u_resolution;

uniform float u_radius;
uniform vec2 u_position;

void main() {

	float distanceToCenter = distance(v_color.xy, u_position);

	if(distanceToCenter < u_radius) {
		fragColor = vec4(v_color);
	} else {
		fragColor = vec4(0.0, 0.0, 0.0, 0.0);
	}

}