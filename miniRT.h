#ifndef MINIRT_H
#define MINIRT_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include "minilibx-linux/mlx.h"

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846
#define ASPECT_RATIO (WIDTH/HEIGHT)

typedef enum e_obj_type
{
    SPHERE,
    PLANE,
    CYLINDER
} t_obj_type;

typedef struct s_sphere
{
    t_vec3  center;     // Kürenin merkez noktası
    double  diameter;   // Çapı (Yarıçap = diameter / 2)
} t_sphere;

typedef struct s_plane
{
    t_vec3  point;      // Düzlem üzerindeki herhangi bir nokta
    t_vec3  normal;     // Düzlemin baktığı yön (normalize edilmiş olmalı)
} t_plane;

typedef struct s_cylinder
{
    t_vec3  center;     // Silindirin merkez noktası
    t_vec3  normal;     // Silindirin uzandığı eksen (normalize edilmiş olmalı)
    double  diameter;   // Çapı
    double  height;     // Yüksekliği
} t_cylinder;

typedef struct s_object
{
    t_obj_type      type;   // Bu obje ne? (SPHERE, PLANE, CYLINDER)
    void            *data;  // Şeklin kendi özel verileri (t_sphere*, t_plane* vb.)
    t_vec3          color;  // Objenin RGB rengi (Ortak özellik)
    struct s_object *next;  // Listedeki bir sonraki objeye işaretçi
} t_object;

typedef struct s_vec3
{
    double x, y, z;
} t_vec3;

typedef struct s_scene
{
	t_object    *objects;
	t_camera camera;
	t_light light;
} t_scene;

typedef struct s_data 
{
    void    *mlx;      // mlx bağlantı pointer'ı
    void    *win;      // pencere pointer'ı
    void    *img;      // imaj pointer'ı
    char    *addr;     // imajın hafızadaki başlangıç adresi
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_data;

typedef struct s_light
{
    t_vec3 position;     // Işığın uzaydaki konumu (origin gibi düşünebilirsin)
    double brightness;   // Işığın parlaklık oranı (0.0 ile 1.0 arası)
    t_vec3 color;        // Işığın RGB rengi
} t_light;

typedef struct s_ray
{
    t_vec3 origin;    // Işının çıktığı nokta
    t_vec3 direction; // Işının gittiği yön (vektör)
} t_ray;

typedef struct s_camera
{
    t_vec3 position;     // Kameranın konumu
    t_vec3 orientation;  // Kameranın baktığı yön (3D vektör)
    int fov;             // Görüş açısı (Field of View)
} t_camera;



t_vec3	vec_add(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_sub(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_mult(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_divide(t_vec3 vector1, t_vec3 vector2);
t_vec3	vec_mult_scalar(t_vec3 vector, double scalar);
t_vec3	vec_divide_scalar(t_vec3 vector, double scalar);
double vec_magnitude(t_vec3 vector);
t_vec3 vec_normalize(t_vec3 vector);
double vec_dot_product(t_vec3 vector1, t_vec3 vector2);
double ndc_x(int x);
double ndc_y(int y);
double fov_factor(int fov);
double check_intersection(t_ray ray, t_object *obj);
t_ray	generate_ray(int x, int y, t_scene *scene, double fov_fact);
int	init_mlx(t_data *data);
void	render_scene(t_data *data, t_scene *scene);
double	get_closest_intersection(t_ray ray, t_object *objects);

#endif