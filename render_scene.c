#include "miniRT.h"

t_ray	generate_ray(int x, int y, t_scene *scene, double fov_fact)
{
	t_ray	ray;
	t_vec3	temp;

	ray.origin = scene->camera.position;
	temp.x = ndc_x(x) * ASPECT_RATIO * fov_fact;
	temp.y = ndc_y(y) * fov_fact;
	temp.z = 1.0;
	ray.direction = vec_normalize(vec_sub(temp, ray.origin));
	return (ray);
}

double	get_closest_intersection(t_ray ray, t_object *objects)
{
	t_object	*current;
	double		closest_t;
	double		current_t;

	current = objects;
	closest_t = -1.0;
	while (current != NULL)
	{
		current_t = check_intersection(ray, current);
		if (current_t > 0 && (closest_t == -1.0 || current_t < closest_t))
			closest_t = current_t;
		current = current->next;
	}
	return (closest_t);
}

int	init_mlx(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "miniRT");
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	return (0);
}

void	render_scene(t_data *data, t_scene *scene)
{
	int		x;
	int		y;
	t_ray	ray;
	double	fov_fact;
	double	closest_t;

	fov_fact = fov_factor(scene->camera.fov);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = generate_ray(x, y, scene, fov_fact);
			closest_t = get_closest_intersection(ray, scene->objects);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}
