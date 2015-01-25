#version 130

in vec4 color;
in vec4 texuv;

uniform bool hasTex;
uniform sampler2D tex;

void main() {
	if(hasTex)
		gl_FragColor = texture(tex, vec2(texuv.x, texuv.y)) * color;
	else
		gl_FragColor = color;
}
