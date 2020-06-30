#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoord;
out vec2 v_texCoord;
out vec4 v_color;

uniform mat4 u_transform;

void main() {
	v_color = vec4(1-a_position.z*2);
	//v_color = vec4(a_position, 1);
	v_texCoord = vec2(a_texCoord.x, 1-a_texCoord.y);
	gl_Position = vec4(a_position, 1)*u_transform;
}
