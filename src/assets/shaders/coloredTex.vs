#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;
layout(location = 2) in vec3 a_color;
out vec2 v_texCoord;
out vec4 v_color;

void main() {
	v_color = vec4(a_color, 1);
	v_texCoord = vec2(a_texCoord.x, 1-a_texCoord.y);
	gl_Position = vec4(a_position.x/8-0.5, a_position.y/6-0.5, 0, 1);
}
