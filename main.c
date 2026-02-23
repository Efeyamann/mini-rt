#include "miniRT.h"

t_scene init_mock_scene()
{
    t_scene     scene;
    t_object    *node;
    t_sphere    *sphere;
    
    node = malloc(sizeof(t_object));
    sphere = malloc(sizeof(t_sphere));
    
    sphere->center = (t_vec3){0.0, 0.0, 5.0};
    sphere->diameter = 2.0;
    
    node->type = SPHERE;
    node->data = sphere;
    node->color = (t_vec3){255.0, 0.0, 0.0};
    node->next = NULL;
    
    scene.objects = node; 
    
    scene.camera.position = (t_vec3){0.0, 0.0, 0.0};
    scene.camera.orientation = (t_vec3){0, 0, 1};
    scene.camera.fov = 90;

    scene.light.position = (t_vec3){-3.0, 6.0, 2.0};
    scene.light.brightness = 0.5;
    scene.light.color = (t_vec3){100.0, 100.0, 100.0};

    return (scene);
}


int	main(void)
{
	t_scene	my_scene;
	t_data	data;

	my_scene = init_mock_scene();
	if (init_mlx(&data) != 0)
	{
		free(my_scene.objects);
		return (1);
	}
	render_scene(&data, &my_scene);
	mlx_loop(data.mlx);
	return (0);
}
