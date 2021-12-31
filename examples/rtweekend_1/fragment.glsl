/* ---------- Shady Specific -------- */

#version 400

in vec2 ScreenResolution;
in vec2 MousePosition;
in float Time;

out vec4 FragColor;

/* ---------------------------------- */

#define FLT_MAX 3.402823466e+38
#define FLT_MIN 1.175494351e-38
#define DBL_MAX 1.7976931348623158e+308
#define DBL_MIN 2.2250738585072014e-308

#define SAMPLES_PER_PIXEL 10
#define MAX_SCENE_SIZE 6
#define MAX_DEPTH 10

#define PI 3.14159265359
#define RAND_CONST 43758.5453
#define RAND_CONST2 0.7260370917943948
#if 0
float seed;
void set_seed(vec2 co){
    seed = fract(sin(mod(dot(co, vec2(12.9898, 78.233)) * RAND_CONST2, PI)) * RAND_CONST);
}
float rand(){
    seed = fract(sin(mod(seed / RAND_CONST2, PI)) * RAND_CONST);
    return seed;
}
#else
float seed[3];
void set_seed(vec2 co) {
    float s = dot(co, vec2(12.9898, 78.233));
    seed[0] = fract(sin(mod(s / RAND_CONST2, PI)) * RAND_CONST);
    seed[1] = fract(sin(mod(seed[0] / RAND_CONST2, PI)) * RAND_CONST);
    seed[2] = fract(sin(mod(seed[1] / RAND_CONST2, PI)) * RAND_CONST);
}
float rand() {
    seed[0] = mod(171.0 * seed[0], 30269.0);
    seed[1] = mod(172.0 * seed[1], 30307.0);
    seed[2] = mod(170.0 * seed[2], 30323.0);
    return fract(seed[0]/30269.0 + seed[1]/30307.0 + seed[2]/30323.0);
}    
#endif

float rand(float min, float max) {
    return rand() * (max - min) + min;
}
vec3 random_in_unit_disk() {
    vec3 direction = vec3(rand(-1.0, 1.0), rand(-1.0, 1.0), 0.0);
    float len = length(direction);
    if (len >= 1.0) {
        float magnitude = rand(0.01, 1.0/len); // Magic number controls black dots btw
        return direction * magnitude; // Scale to magnitude between 0..1
    } else {
        return direction;
    }
}
vec3 random_in_unit_sphere() {
    //for (int i = 0; i < 10; i++) {
    //    vec3 direction = vec3(rand(-1.0, 1.0), rand(-1.0, 1.0), rand(-1.0, 1.0));
    //    if (length(direction) < 1.0) {
    //        return direction;
    //    }
    //}
    //return vec3(0.57);
    vec3 direction = vec3(rand(-1.0, 1.0), rand(-1.0, 1.0), rand(-1.0, 1.0));
    float len = length(direction);
    if (len >= 1.0) {
        float magnitude = rand(0.01, 1.0/len); // Magic number controls black dots btw
        return direction * magnitude; // Scale to magnitude between 0..1
    } else {
        return direction;
    }
}
vec3 random_unit_vector() {
    return normalize(random_in_unit_sphere());
}
vec3 random_in_hemisphere(vec3 normal) {
    vec3 v = random_in_unit_sphere();
    return (dot(v, normal) > 0.0) ? v : -v;
}

float fmin(float f1, float f2) { return f1 <= f2 ? f1 : f2; }
float fmax(float f1, float f2) { return f1 >= f2 ? f1 : f2; }

bool near_zero(vec3 v) {
    const float s = 1e-8;
    return abs(v.x) < s && abs(v.y) < s && abs(v.z) < s;
}
vec3 reflect(vec3 v, const vec3 normal) {
    return v - 2.0 * dot(v, normal) * normal;
}
vec3 refract(vec3 v, vec3 normal, float ratio) {
    float angle = fmin(dot(-v, normal), 1.0);
    vec3 perpendicular = ratio * (v + angle * normal);
    vec3 parallel = -sqrt(abs(1.0 - length(perpendicular) * length(perpendicular))) * normal;
    return perpendicular + parallel;
}
float reflectance(float cosine, float reflective_index) {
    float r0 = (1.0 - reflective_index) / (1.0 + reflective_index);
    r0 *= r0;
    return r0 + (1.0 - r0) * pow(1.0 - cosine, 5.0);
}

struct Ray {
    vec3 origin;
    vec3 direction;
};
struct Camera {
    vec3 origin;
    vec3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    float lens_radius;
};
struct Material {
    int type;
    vec3 colour;
    float fuzz;
    float refractive_index;
};
Material Lambertian_Material(vec3 colour) {
    return Material(0, colour, 0.0, 0.0);
}
Material Metal_Material(vec3 colour, float fuzz) {
    return Material(1, colour, fuzz, 0.0);
}
Material Dielectric_Material(float refractive_index) {
    return Material(2, vec3(0.0), 0.0, refractive_index);
}
struct HitRecord {
    vec3 position;
    vec3 normal;
    Material material;
    float distance;
    bool front_face;
};
struct Sphere {
    vec3 center;
    float radius;
    Material material;
};
struct World {
    Sphere scene[MAX_SCENE_SIZE];
    int length;
};

World world;
Camera camera;

vec3 ray_at(Ray ray, float time) {
    return (ray.origin + time * ray.direction);
}
Camera camera_new(vec3 look_from, vec3 look_at, vec3 vup, float vfov, float aspect, float aperture, float focus_distance) {
    Camera camera;
    
    float theta = radians(vfov);
    float h = tan(theta / 2.0);
    vec2 viewport = vec2(aspect, 1.0) * 2.0 * h;
    
    camera.w = normalize(look_from - look_at);
    camera.u = normalize(cross(vup, camera.w));
    camera.v = cross(camera.w, camera.u);
    

    // Setup camera / ray
    camera.origin = look_from;
    camera.horizontal = viewport.x * camera.u * focus_distance;
    camera.vertical = viewport.y * camera.v * focus_distance;
    camera.lower_left_corner = camera.origin - camera.horizontal / 2.0 - camera.vertical / 2.0 - camera.w * focus_distance;
    camera.lens_radius = aperture / 2.0;
    return camera;
}
Ray camera_get_ray(in Camera camera, vec2 uv) {
    vec3 point_on_lens = camera.lens_radius * random_in_unit_disk();
    vec3 offset = camera.u * point_on_lens.x + camera.v * point_on_lens.y;
    offset /= 1000.0;
    
    return Ray(camera.origin + offset, camera.lower_left_corner + uv.x * camera.horizontal + uv.y * camera.vertical - camera.origin - offset);
}
void world_add(Sphere sphere) {
    world.scene[world.length] = sphere;
    world.length++;
}

void hit_record_set_face_normal(inout HitRecord record, Ray r, vec3 outward_normal) {
    record.front_face = dot(r.direction, outward_normal) < 0.0;
    record.normal = record.front_face ? outward_normal : -outward_normal;
}

bool lambertian_scatter(in Material material, in Ray ray, in HitRecord hit, out vec3 attenuation, inout Ray scattered) {
    vec3 scatter_direction = hit.normal + random_unit_vector();
    if (near_zero(scatter_direction)) {
        scatter_direction = hit.normal;
    }
    scattered = Ray(hit.position, scatter_direction);
    attenuation = material.colour;
    return true;
}
bool metal_scatter(in Material material, in Ray ray, in HitRecord hit, out vec3 attenuation, inout Ray scattered) {
    vec3 reflected = reflect(normalize(ray.direction), hit.normal);
    scattered = Ray(hit.position, reflected + material.fuzz * random_in_unit_sphere());
    attenuation = material.colour;
    return dot(scattered.direction, hit.normal) > 0.0;
}
bool dielectric_scatter(in Material material, in Ray ray, in HitRecord hit, out vec3 attenuation, inout Ray scattered) {
    attenuation = vec3(1.0);
    float refraction_ratio = hit.front_face ? (1.0 / material.refractive_index) : material.refractive_index;
    
    vec3 unit_direction = normalize(ray.direction);
    float cos_theta = fmin(dot(-unit_direction, hit.normal), 1.0);
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
    
    bool should_reflect = refraction_ratio * sin_theta > 1.0 || reflectance(cos_theta, refraction_ratio) > rand();
    vec3 direction = should_reflect ? reflect(unit_direction, hit.normal) : refract(unit_direction, hit.normal, refraction_ratio);
    
    scattered = Ray(hit.position, direction);
    return true;
}
bool scatter(in Material material, in Ray ray, in HitRecord hit, out vec3 attenuation, inout Ray scattered) {
    switch (material.type) {
        case 0:
            return lambertian_scatter(material, ray, hit, attenuation, scattered);
        case 1:
            return metal_scatter(material, ray, hit, attenuation, scattered);
        case 2:
            return dielectric_scatter(material, ray, hit, attenuation, scattered);
    }
    return false;
}

bool sphere_hit(Sphere sphere, Ray ray, float min_distance, float max_distance, inout HitRecord hit) {
    vec3 oc = ray.origin - sphere.center;
    float a = length(ray.direction) * length(ray.direction);
    float half_b = dot(oc, ray.direction);
    float c = length(oc) * length(oc) - sphere.radius * sphere.radius;
    float discriminant = half_b * half_b - a * c;
    
    if (discriminant < 0.0) {
        return false;
    }

    float sqrt_discriminant = sqrt(discriminant);

    // Check if there is a root which lies within the range specificied
    // If none return false
    float root = (-half_b - sqrt_discriminant) / a;
    if (root < min_distance || max_distance < root) {
        root = (-half_b + sqrt_discriminant) / a;
        if (root < min_distance || max_distance < root) {
            return false;
        }
    }

    hit.distance = root;
    hit.position = ray_at(ray, root);
    vec3 outward_normal = (hit.position - sphere.center) / sphere.radius;
    hit_record_set_face_normal(hit, ray, outward_normal);
    hit.material = sphere.material;
    return true;
}

bool world_hit(Ray ray, float min_distance, float max_distance, inout HitRecord hit) {
    bool hit_anything = false;
    float closest_so_far = max_distance;
    
    for (int i = 0; i < MAX_SCENE_SIZE; i++) {
        if (i >= world.length) { break; }
        if (sphere_hit(world.scene[i], ray, min_distance, closest_so_far, hit)) {
            hit_anything = true;
            closest_so_far = hit.distance;
        }
    }

    return hit_anything;
}
vec3 ray_color(Ray ray) {
    HitRecord hit;
    vec3 colour = vec3(1.0);
    for (int depth = 0; depth < MAX_DEPTH; depth++) {
        if (world_hit(ray, 0.01, FLT_MAX, hit)) {
            vec3 attenuation;
            if (scatter(hit.material, ray, hit, attenuation, ray)) {
                colour *= attenuation;
            } else {
                //return vec3(1.0, 0.0, 0.0);
                return vec3(0.0);
            }
        } else {
            vec3 unit_direction = normalize(ray.direction);
            float t = 0.5 * (unit_direction.y + 1.0);
            return colour * ((1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0));
        }
    }
    return vec3(0.0);
    ///return pow(0.5, float(MAX_DEPTH)) * vec3(0.0);
}
vec3 ray_color_no_material(Ray ray) {
    HitRecord hit;
    for (int depth = 0; depth < MAX_DEPTH; depth++) {
        if (world_hit(ray, 0.01, FLT_MAX, hit)) {
            //ray = Ray(hit.position, random_in_hemisphere(hit.normal)); // Black dots on the left
            //ray = Ray(hit.position, hit.normal + normalize(random_in_unit_sphere())); // Stuff on the right
            ray = Ray(hit.position, hit.normal + random_in_hemisphere(hit.normal)); //best?!?!
        } else {
            vec3 unit_direction = normalize(ray.direction);
            float t = 0.5 * (unit_direction.y + 1.0);
            return pow(0.5, float(depth)) * ((1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0));
        }
    }

    return pow(0.5, float(MAX_DEPTH)) * vec3(0.0);
}

void setup(vec2 fragCoord) {
    set_seed(fragCoord/ScreenResolution.xy * Time); // Add time for frame to frame randomness

    vec3 look_from = vec3(3.0, 10.0, sin(Time) + 2.0);
    vec3 look_at = vec3(0.0, 0.0, -1.0);
    vec3 vup = vec3(0.0, 1.0, 0.0);
    float aspect = ScreenResolution.x / ScreenResolution.y;
    float dist_to_focus = length(look_from - look_at);
    float aperture = 2.0;
    camera = camera_new(look_from, look_at, vup, 20.0, aspect, dist_to_focus, aperture);
       
    // Materials  
    Material m_lam_white  = Lambertian_Material(vec3(.8));
    Material m_lam_yellow = Lambertian_Material(vec3(1, .8, .36));
    Material m_lam_red    = Lambertian_Material(vec3(1, .43, .41));
    Material m_dialetric  = Dielectric_Material(1.5);
    Material m_metal      = Metal_Material(vec3(.8), 0.0);

    // Some offsets
    vec3 left   = vec3(-1, 0, 0);
    vec3 right  = vec3(1, 0, 0);
    vec3 bottom = vec3(0, 0, -1);

    // Scene Spheres
    Sphere ground       = Sphere(vec3(0.0, -100.5, 0.0) + bottom, 100.0, m_lam_white);
    Sphere lambertian_1 = Sphere(vec3(0.0) + bottom,               0.5, m_lam_yellow);
    Sphere lambertian_2 = Sphere(vec3(0.0) + bottom + left,        0.5,  m_lam_red);
    Sphere metal        = Sphere(vec3(0.0) + bottom + right,       0.5,  m_metal);
    Sphere dialetric_1  = Sphere(vec3(0.0) + bottom,               0.5,  m_dialetric);
    Sphere dialetric_2  = Sphere(vec3(0.0) + bottom,               0.48, m_dialetric);

    // Add spheres to scene
    world_add(ground);
    world_add(lambertian_1);
    world_add(lambertian_2);
    world_add(metal);
    world_add(dialetric_1);
    world_add(dialetric_2);
}

void main() {
    // move center sphere
    world.scene[1].center.z = sin(Time)*2 - 1;
    world.scene[1].center.x = cos(Time)*2;
    // world.scene[1].radius = abs(sin(Time))*.5+.2;

    setup(gl_FragCoord.xy);
    vec2 uv = gl_FragCoord.xy/ScreenResolution.xy;

    // Do actual ray tracing
    vec3 col;
    for (int i = 0; i < SAMPLES_PER_PIXEL; i++) {
        vec2 rand_ray = uv + vec2(rand(), rand()) / ScreenResolution.xy;
        Ray ray = camera_get_ray(camera, rand_ray);
        col += ray_color(ray);
    }
    col /= float(SAMPLES_PER_PIXEL);
    col = sqrt(col);

    // Output to screen
    FragColor = vec4(col, 1.0);
}