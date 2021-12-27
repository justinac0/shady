#version 400

out vec4 FragColor;
in float Time;

void main() {
    FragColor = vec4(Time);
}
