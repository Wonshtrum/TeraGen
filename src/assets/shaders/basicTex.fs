#version 330 core

in vec2 v_texCoord;
in vec4 v_color;
layout(location = 0) out vec4 color;

uniform sampler2D u_texture;

void main() {
	color = v_color*texture2D(u_texture, v_texCoord);
}
