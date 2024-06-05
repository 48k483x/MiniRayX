#include "miniRT.h"

Vec3 calculate_lighting(Vec3 point, Vec3 normal, Vec3 view_dir, Light light, Sphere sphere) {
    Vec3 light_dir = vec3_normalize(vec3_sub(light.position, point));

    // Ambient
    float ambient_strength = 0.1;
    Vec3 ambient = vec3_scale(sphere.color, ambient_strength);

    // Diffuse
    float diff = fmax(vec3_dot(normal, light_dir), 0.0);
    Vec3 diffuse = vec3_scale(sphere.color, diff * light.intensity);

    // Specular
    float specular_strength = 0.5;
    Vec3 reflect_dir = vec3_sub(vec3_scale(normal, 2 * vec3_dot(light_dir, normal)), light_dir);
    float spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 32);
    Vec3 specular = vec3_scale(light.color, specular_strength * spec);

    Vec3 result = vec3_add(vec3_add(ambient, diffuse), specular);
    return result;
}
