#include "miniRT.h"
#include <math.h>

int is_in_shadow(Ray shadow_ray, Sphere sphere, Plane plane1, Plane plane2, float light_distance)
{
    float t;
    if (ray_intersect_sphere(shadow_ray, sphere, &t) && t > 0.001 && t < light_distance)
        return 1;
    if (ray_intersect_plane(shadow_ray, plane1, &t) && t > 0.001 && t < light_distance)
        return 1;
    if (ray_intersect_plane(shadow_ray, plane2, &t) && t > 0.001 && t < light_distance)
        return 1;
    return 0;
}

Vec3 calculate_lighting(Vec3 point, Vec3 normal, Vec3 view_dir, Light light, Vec3 object_color, 
                        Sphere sphere, Plane plane1, Plane plane2)
{
    // Normalize vectors
    normal = vec3_normalize(normal);
    view_dir = vec3_normalize(view_dir);

    // Calculate light direction and distance
    Vec3 light_dir = vec3_sub(light.position, point);
    float light_distance = vec3_length(light_dir);
    light_dir = vec3_normalize(light_dir);

    // Ambient lighting
    float ambient_strength = 0.1;
    Vec3 ambient = vec3_scale(object_color, ambient_strength);

    // Check for shadows
    Ray shadow_ray = {point, light_dir};
    if (is_in_shadow(shadow_ray, sphere, plane1, plane2, light_distance))
    {
        // If in shadow, only return ambient light
        return ambient;
    }

    // Diffuse lighting
    float diff = fmax(vec3_dot(normal, light_dir), 0.0);
    Vec3 diffuse = vec3_scale(vec3_scale(object_color, light.intensity), diff);

    // Specular lighting
    float specular_strength = 0.5;
    Vec3 reflect_dir = vec3_sub(vec3_scale(normal, 2.0 * vec3_dot(light_dir, normal)), light_dir);
    float spec = pow(fmax(vec3_dot(view_dir, reflect_dir), 0.0), 32);
    Vec3 specular = vec3_scale(light.color, specular_strength * spec * light.intensity);

    // Combine all lighting components
    Vec3 result = vec3_add(vec3_add(ambient, diffuse), specular);

    // Ensure color values are between 0 and 1
    result.x = fmin(result.x, 1.0);
    result.y = fmin(result.y, 1.0);
    result.z = fmin(result.z, 1.0);

    return result;
}