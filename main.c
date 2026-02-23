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

int main()
{
	int x;
	int y;
	t_scene my_scene;
	t_data data;
	t_ray ray;
	double fov_fact;
	t_vec3 temp;

	my_scene = init_mock_scene();
	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		free(my_scene.objects);
		return(1);
	}
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "miniRT");
	data.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	y = 0;
    fov_fact = fov_factor(my_scene.camera.fov);
    while (y < HEIGHT)
    {
        x = 0;
        while(x < WIDTH)
        {
            ray.origin = my_scene.camera.position;
            temp.x = ndc_x(x) * ASPECT_RATIO * fov_fact;
            temp.y = ndc_y(y) * fov_fact;
            temp.z = 1.0;
			ray.direction = vec_normalize(vec_sub(temp, ray.origin));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data.mlx, data.win, data.img, 0, 0);
	mlx_loop(data.mlx);
}
