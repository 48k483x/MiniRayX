#include "miniRT.h"

void init_scene(t_scene *scene)
{
    scene->amb.intensity = 0.2;
    scene->amb.color = (t_vec3){1.0, 1.0, 1.0};

    scene->cam.origin = (t_vec3){0, 0, 15};
    scene->cam.normal = (t_vec3){0, 0, -1};
    scene->cam.fov = 80;

    scene->light.origin = (t_vec3){-20, 5, 40};
    scene->light.intensity = 0.6;
    scene->light.color = (t_vec3){1, 1, 1};

    t_sph_l *sphere = malloc(sizeof(t_sph_l));
    sphere->sph.origin = (t_vec3){0, 0, 30};
    sphere->sph.diameter = 5;
    sphere->sph.color = (t_vec3){1, 0, 0};
    sphere->next = NULL;
    scene->sph = sphere;

    t_pla_l *plane1 = malloc(sizeof(t_pla_l));
    plane1->pla.origin = (t_vec3){0, -2.5, 0};
    plane1->pla.normal = (t_vec3){0, 1, 0};
    plane1->pla.color = (t_vec3){0, 1, 1};
    plane1->next = NULL;

    t_pla_l *plane2 = malloc(sizeof(t_pla_l));
    plane2->pla.origin = (t_vec3){0, 0, 50};
    plane2->pla.normal = (t_vec3){0, 0, 1};
    plane2->pla.color = (t_vec3){0.498, 0.514, 0.737};
    plane2->next = plane1;
    scene->pla = plane2;

    scene->cyl = NULL;
}

void free_scene(t_scene *scene)
{
    t_sph_l *sph_tmp;
    while (scene->sph)
    {
        sph_tmp = scene->sph;
        scene->sph = scene->sph->next;
        free(sph_tmp);
    }

    t_pla_l *pla_tmp;
    while (scene->pla)
    {
        pla_tmp = scene->pla;
        scene->pla = scene->pla->next;
        free(pla_tmp);
    }

    t_cyl_l *cyl_tmp;
    while (scene->cyl)
    {
        cyl_tmp = scene->cyl;
        scene->cyl = scene->cyl->next;
        free(cyl_tmp);
    }
}