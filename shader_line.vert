#version 450

layout (location = 0) in vec2 in_vPos;

out vec4 v_dotInfo;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;

uniform vec2 u_origin;
uniform vec2 u_end;
uniform vec2 u_dot;

void main() {
	//gl_Position = vec4(in_vPos.x, in_vPos.y, 0.0, 1.0);
	vec4 newPos;

	if(gl_VertexID == 0) {
		newPos = vec4(u_origin.x, u_origin.y, 0.5, 1.0);
	} else if(gl_VertexID == 1) {
		newPos = vec4(u_dot.x, u_dot.y, 0.5, 1.0);
	} else if(gl_VertexID == 2) {
		newPos = vec4(u_dot.x, u_dot.y, 1.0, 1.0);
	}

	//float dist = 1.0 - length(newPos.xy);
	//v_dotInfo = vec4(1.0, 1.0, 1.0, step(dist, newPos.z));
	v_dotInfo = newPos;

	gl_Position = u_projection * u_view * vec4(newPos.x, newPos.y, 1.0, 1.0);
}