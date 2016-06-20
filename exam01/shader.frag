#version 400

out vec4 outputColor;

smooth in vec4 theColor;
uniform float time;
uniform float fragLoopDuration;

const vec4 firstColor = vec4(1.0f,1.0f,1.0f,1.0f);
const vec4 secondColor = vec4(0.0f,0.0f,0.0f,1.0f);

void main() {
	float currTime = mod(time, fragLoopDuration);
	float currLerp = currTime / fragLoopDuration;
	outputColor = mix(firstColor, secondColor, currLerp);
}