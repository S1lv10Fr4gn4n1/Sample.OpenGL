#version 400
out vec4 outputColor;

void main() {
	float lerpValue = gl_FragCoord.y / 500.0f;
	outputColor = mix(vec4(1.0, 1.0, 1.0, 1.0), vec4(0.0, 0.0, 0.0, 0.0), lerpValue);
}