#version 130

in vec4 vertex_position;
in vec4 vertex_normal;
in vec4 vertex_color;
in vec4 vertex_texuv;

out vec4 color;
out vec4 texuv;

uniform mat4 camera;
uniform mat4 model;

void main() {
	gl_Position = camera * model * vertex_position;
	
	color = vertex_color;
	texuv = vertex_texuv;
}
