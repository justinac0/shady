#version 400

layout (location = 0) in vec3 position;

// Uniforms
//

// Screen Resolution
uniform float u_ScreenResolution_x;
uniform float u_ScreenResolution_y;
out vec2 ScreenResolution;

// Mouse Position
uniform float u_Mouse_x;
uniform float u_Mouse_y;
out vec2 MousePosition;

// Time
uniform float u_Time;
out float Time;

void main() {
    gl_Position = vec4(position, 1.0);
    
    ScreenResolution = vec2(u_ScreenResolution_x, u_ScreenResolution_y);
    MousePosition    = vec2(u_Mouse_x, u_Mouse_y);
    Time             = u_Time;
}
