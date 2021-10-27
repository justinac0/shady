#version 400

out vec4 FragColor;

in vec2  ScreenResolution;
in vec2  MousePosition;
in float Time;

void main() {
    vec2 uv = (gl_FragCoord.xy - 0.5 * ScreenResolution.xy) / ScreenResolution.y;
    vec2 mouse = MousePosition / ScreenResolution;

    float f = smoothstep(0.2, 0.21, length(uv));
    vec3 col = vec3(f);
    FragColor = vec4(col, 1);
}
