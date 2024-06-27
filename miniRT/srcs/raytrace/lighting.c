#include "../include/miniRT.h"

t_vec3 calculate_light(t_light_params params) {
    // Normalize vectors
    params.normal = vec3_normalize(params.normal);
    params.view_dir = vec3_normalize(params.view_dir);

    // Calculate light direction and distance
    t_vec3 light_dir = vec3_sub(params.light.origin, params.point);
    float light_distance = vec3_length(light_dir);
    light_dir = vec3_normalize(light_dir);

    // Ambient lighting
    float ambient_strength = 0.1;
    t_vec3 ambient = vec3_scale(params.object_color, ambient_strength);

    // // Check for shadows
    // t_ray shadow_ray = {params.point, light_dir};
    // if (is_in_shadow(shadow_ray, params.spheres, params.planes, params.cylinders, light_distance)) {
    //     // If in shadow, only return ambient light
    //     return ambient;
    // }

    // Diffuse lighting
    float diff = fmax(vec3_dot(params.normal, light_dir), 0.0);
    t_vec3 diffuse = vec3_scale(vec3_scale(params.object_color, params.light.intensity), diff);

    // Specular lighting
    float specular_strength = 0.5;
    t_vec3 reflect_dir = vec3_sub(vec3_scale(params.normal, 2.0 * vec3_dot(light_dir, params.normal)), light_dir);
    float spec = pow(fmax(vec3_dot(params.view_dir, reflect_dir), 0.0), 32);
    t_vec3 specular = vec3_scale(params.light.color, specular_strength * spec * params.light.intensity);

    // Combine all lighting components
    t_vec3 result = vec3_add(vec3_add(ambient, diffuse), specular);

    // Ensure color values are between 0 and 1
    result.x = fmin(result.x, 1.0);
    result.y = fmin(result.y, 1.0);
    result.z = fmin(result.z, 1.0);

    return result;
}
