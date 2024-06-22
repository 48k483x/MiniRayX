#include "../include/miniRT.h"

void print_vec3(t_vec3 vec) {
    printf("Vec3(x: %.2f, y: %.2f, z: %.2f)\n", vec.x, vec.y, vec.z);
}

void print_sphere_list(t_sph_l *sph) {
    while (sph) {
        printf("Sphere Origin: ");
        print_vec3(sph->sph.origin);
        printf("Diameter: %.2f\n", sph->sph.diameter);
        printf("Color: %d\n", sph->sph.color);
        sph = sph->next;
    }
}

void print_plane_list(t_pla_l *pla) {
    while (pla != NULL) {
        printf("Plane Origin: ");
        print_vec3(pla->pla.origin);
        printf("Normal: ");
        print_vec3(pla->pla.normal);
        printf("Color: %d\n", pla->pla.color);
        pla = pla->next;
    }
}

void print_cylinder_list(t_cyl_l *cyl) {
    while (cyl != NULL) {
        printf("Cylinder Origin: ");
        print_vec3(cyl->cyl.origin);
        printf("Normal: ");
        print_vec3(cyl->cyl.normal);
        printf("Diameter: %.2f\n", cyl->cyl.diameter);
        printf("Height: %.2f\n", cyl->cyl.height);
        printf("Color: %d\n", cyl->cyl.color);
        cyl = cyl->next;
    }
}

void print_scene(t_scene *scene) {
    printf("Ambient Intensity: %.2f\n", scene->amb.intensity);
    printf("Ambient Color: %d\n", scene->amb.color);
    
    printf("Camera Origin: ");
    print_vec3(scene->cam.origin);
    printf("Camera Normal: ");
    print_vec3(scene->cam.normal);
    printf("Camera FOV: %.2f\n", scene->cam.fov);
    
    printf("Light Origin: ");
    print_vec3(scene->light.origin);
    printf("Light Intensity: %.2f\n", scene->light.intensity);
    printf("Light Color: %d\n", scene->light.color);
    
    printf("\nSpheres:\n");
    print_sphere_list(scene->sph);
    
    // printf("\nPlanes:\n");
    // print_plane_list(scene->pla);
    
    // printf("\nCylinders:\n");
    // print_cylinder_list(scene->cyl);
}