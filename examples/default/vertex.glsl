#version 400

layout (location = 0) in vec3 position;

// Uniforms
//

// Screen Resolution
uniform vec2 uResolution;
out     vec2 Resolution;

// Mouse Position
uniform vec2 uMouse;
out     vec2 Mouse;

// Time
uniform float uTime;
out     float Time;

void main() {
    gl_Position = vec4(position, 1.0);
    
    Resolution = uResolution;
    Mouse = uMouse;
    Time = uTime;
}
