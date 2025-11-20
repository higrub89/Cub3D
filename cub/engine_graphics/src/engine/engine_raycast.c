
#include "../../include/cube3D.h"

// Paso 1: Inicializar vectores del rayo y delta
void	ft_init_ray(t_ray *ray, t_grl *grl, int x)
{
	ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = grl->player.dir_x + grl->player.plane_x * ray->camera_x;
	ray->ray_dir_y = grl->player.dir_y + grl->player.plane_y * ray->camera_x;
	ray->map_x = (int)grl->player.pos_x;
	ray->map_y = (int)grl->player.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

// Paso 2: Calcular step y side_dist inicial
void	ft_calc_step(t_ray *ray, t_grl *grl)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (grl->player.pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - grl->player.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (grl->player.pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - grl->player.pos_y)
			* ray->delta_dist_y;
	}
}

// Paso 3: Ejecutar DDA hasta golpear pared
void	ft_perform_dda(t_ray *ray, t_grl *grl)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (grl->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

// Paso 4: Calcular altura de linea y puntos de dibujo
void	ft_calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
		// modificacion para ver el cielo.
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (ray->draw_end >= WIN_HEIGHT)
		ray->draw_end = WIN_HEIGHT - 1;
}

// Paso 5: Elegir color (Temporal hasta texturas)
void	ft_get_wall_color(t_ray *ray)
{
	if (ray->side == 0) // Pared Este/Oeste
		ray->color = 0x00FF00;
	else // Pared Norte/Sur
		ray->color = 0xFF0000;

	// Sombreado simple
	if (ray->side == 1)
		ray->color = 0x7F0000;
}