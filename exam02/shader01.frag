#version 400

out vec4 frag_colour;
smooth in vec4 theColor;

void main() {
	frag_colour = theColor;
}