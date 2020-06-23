#version 330 core

layout(location = 0) in vec3 a_position;
out vec4 v_color;

void main() {
	vec4 position = vec4(a_position/48-0.5, 0, 1);
	gl_Position = position;
	v_color = vec4((1.0+position.xy)/2.0, 0, 1);
}
