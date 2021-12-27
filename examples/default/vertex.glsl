#version 400

layout (location = 0) in vec3 position;

uniform float u_Time;
out float Time;

void main() {
    gl_Position = vec4(position, 1.0);
    Time = u_Time;
}