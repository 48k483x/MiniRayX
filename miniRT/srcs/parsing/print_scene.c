#include "../include/miniRT.h"

void print_vec3(t_vec3 vec) {
    printf("(x: %.2f, y: %.2f, z: %.2f)\n", vec.x, vec.y, vec.z);
}

void print_sphere_list(t_sph_l *sph) {
    t_sph_l *tmp = sph;
    int index = 0;
    while (tmp != NULL) {
        printf("  Sphere %d:\n", index);
        printf("    Origin: ");
        print_vec3(tmp->sph.origin);
        printf("    Diameter: %.2f\n", tmp->sph.diameter);
        printf("    Color: %d\n", tmp->sph.color);
        tmp = tmp->next;
        index++;
        if (tmp) printf("  -------------------------\n");
    }
}

void print_plane_list(t_pla_l *pla) {
    int index = 0;
    while (pla != NULL) {
        printf("  Plane %d:\n", index);
        printf("    Origin: ");
        print_vec3(pla->pla.origin);
        printf("    Normal: ");
        print_vec3(pla->pla.normal);
        printf("    Color: %d\n", pla->pla.color);
        pla = pla->next;
        index++;
        if (pla) printf("  -------------------------\n");
    }
}

void print_cylinder_list(t_cyl_l *cyl) {
    int index = 0;
    while (cyl != NULL) {
        printf("  Cylinder %d:\n", index);
        printf("    Origin: ");
        print_vec3(cyl->cyl.origin);
        printf("    Normal: ");
        print_vec3(cyl->cyl.normal);
        printf("    Diameter: %.2f\n", cyl->cyl.diameter);
        printf("    Height: %.2f\n", cyl->cyl.height);
        printf("    Color: %d\n", cyl->cyl.color);
        cyl = cyl->next;
        index++;
        if (cyl) printf("  -------------------------\n");
    }
}

void print_scene(t_scene *scene) {
    printf("Ambient Light:\n");
    printf("  Intensity: %.2f\n", scene->amb.intensity);
    printf("  Color: %d\n", scene->amb.color);
    printf("\n");

    printf("Camera:\n");
    printf("  Origin: ");
    print_vec3(scene->cam.origin);
    printf("  Normal: ");
    print_vec3(scene->cam.normal);
    printf("  FOV: %.2f\n", scene->cam.fov);
    printf("\n");

    printf("Light:\n");
    printf("  Origin: ");
    print_vec3(scene->light.origin);
    printf("  Intensity: %.2f\n", scene->light.intensity);
    printf("  Color: %d\n", scene->light.color);
    printf("\n");

    printf("Spheres:\n");
    print_sphere_list(scene->sph);
    printf("\n");

    printf("Planes:\n");
    print_plane_list(scene->pla);
    printf("\n");

    printf("Cylinders:\n");
    print_cylinder_list(scene->cyl);
    printf("\n");
}