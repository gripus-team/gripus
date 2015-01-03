#version 130

in vec4 vertex_position;
in vec4 vertex_color;
out vec4 color;

uniform mat4 camera;

void main() {
	gl_Position = camera * vertex_position;
	color = vertex_color;
}
