#version 400

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform float time;
uniform float loopDuration;

smooth out vec4 theColor;

vec4 getTotalOffset() {
	float timeScale = 3.14159f * 2.0f / loopDuration;
    
    float currTime = mod(time, loopDuration);
    vec4 totalOffset = vec4(
        cos(currTime * timeScale) * 0.5f,
        sin(currTime * timeScale) * 0.5f,
        0.0f,
        0.0f);
        
    return totalOffset;
}

void main() {
	gl_Position = position + getTotalOffset();
	theColor = color;
}