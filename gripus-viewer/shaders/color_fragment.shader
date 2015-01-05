#version 130

in vec4 color;
in vec4 texuv;

uniform sampler2D tex;

void main() {
	gl_FragColor = texture(tex, vec2(texuv.x, texuv.y)) * color;
}
