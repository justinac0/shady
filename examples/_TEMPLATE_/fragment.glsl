#version 400

out vec4 FragColor;

in vec2  ScreenResolution;
in vec2  MousePosition;
in float Time;

void main() {
    FragColor = vec4(cos(Time), sin(Time), sin(Time), 1);
}
