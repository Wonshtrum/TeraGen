#version 330 core

layout(location = 0) in vec2 a_position;
out vec4 v_position;

void main() {
	v_position = vec4(a_position/16-0.5, 0, 1);
	gl_Position = v_position;
}
