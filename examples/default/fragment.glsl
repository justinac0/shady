#version 400

in vec2 Resolution;
in vec2 Mouse;
in float Time;

out vec4 FragColor;

void main() {
    vec2 uv = gl_FragCoord.xy / Resolution.xy;

    vec3 col = 0.5 + 0.5 * cos(Time + uv.xyx + vec3(0,2,4));

    FragColor = vec4(col,1.0);
}