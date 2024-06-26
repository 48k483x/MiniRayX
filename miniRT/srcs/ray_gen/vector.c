#include "../include/miniRT.h"

t_vec3 vec3_add(t_vec3 a, t_vec3 b)
{
    return (t_vec3){a.x + b.x, a.y + b.y, a.z + b.z};
}

t_vec3 vec3_sub(t_vec3 a, t_vec3 b)
{
    return (t_vec3){a.x - b.x, a.y - b.y, a.z - b.z};
}

t_vec3 vec3_scale(t_vec3 v, float s)
{
    return (t_vec3){v.x * s, v.y * s, v.z * s};
}

float vec3_dot(t_vec3 a, t_vec3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

t_vec3 vec3_cross(t_vec3 a, t_vec3 b)
{
    return (t_vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

float vec3_length(t_vec3 v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vec3 vec3_normalize(t_vec3 v)
{
    float mag = vec3_length(v);
    return vec3_scale(v, 1.0 / mag);
}
