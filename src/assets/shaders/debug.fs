#version 330 core

in vec4 v_position;
layout(location = 0) out vec4 color;

void main() {
	color = vec4(1,0,0,1);
	color = 0.5*(v_position+1);
}
