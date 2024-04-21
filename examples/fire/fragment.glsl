// adapted from: https://www.shadertoy.com/view/lcGGzK
#version 400

in vec2 Resolution;
in vec2 Mouse;
in float Time;

out vec4 FragColor;


float gyroid (vec3 p) { return dot(cos(p),sin(p.yzx)); }

float fbm(vec3 p) {
    float result = 0.;
    float a = .5;
    for (float i = 0.; i < 9.; ++i)
    {
        p.z += (result+Time)*.1;
        result += abs(gyroid(p/a)*a);
        a /= 1.5;
    }
    return result;
}

void main() {
    vec2 uv = (2.*gl_FragCoord.xy-Resolution.xy)/Resolution.y;
    vec3 ray = normalize(vec3(uv,.5));
    
    vec3 e = vec3(.1*vec2(Resolution.x/Resolution.y), 0.);
    #define T(u) fbm(ray+u)
    vec3 normal = normalize(T(0.)-vec3(T(e.xzz),T(e.zyz),1.));
    vec3 color = 0.2 + 1. * cos(vec3(1,2,3)*5.5 + normal.y);

    FragColor = vec4(color,1.0);
}
