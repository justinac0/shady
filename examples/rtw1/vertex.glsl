#version 400

layout (location = 0) in vec3 position;

// Uniforms
//

// Screen Resolution
uniform vec2 u_ScreenResolution;
out     vec2 ScreenResolution;

// Mouse Position
uniform vec2 u_Mouse;
out     vec2 MousePosition;

// Time
uniform float u_Time;
out     float Time;

void main() {
    gl_Position = vec4(position, 1.0);
    
    ScreenResolution = u_ScreenResolution;
    MousePosition    = u_Mouse;
    Time             = u_Time;
} 