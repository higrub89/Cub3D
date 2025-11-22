/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:05:26 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/22 23:05:36 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	ft_put_pixel(t_grl *grl, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = grl->engine.screen_buff.addr
		+ (y * grl->engine.screen_buff.line_len
			+ x * (grl->engine.screen_buff.bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief Versión OPTIMIZADA de pintado de suelo y techo.
 * Usa aritmética de punteros para evitar multiplicaciones en cada pixel.
 * Floor = assets.colors_rgb[0], Ceiling = assets.colors_rgb[1]
 */
void	ft_render_floor_ceiling(t_grl *grl)
{
	int		x;
	int		y;
	int		*pixel_ptr;
	int		half_height;
	int		ceiling_c;
	int		floor_c;

	half_height = WIN_HEIGHT / 2;
	floor_c = grl->assets.colors_rgb[0];   // Asumimos index 0 = Floor
	ceiling_c = grl->assets.colors_rgb[1]; // Asumimos index 1 = Ceiling

	// 1. TECHO (Mitad superior)
	y = 0;
	while (y < half_height)
	{
		pixel_ptr = (int *)(grl->engine.screen_buff.addr
				+ (y * grl->engine.screen_buff.line_len));
		x = 0;
		while (x < WIN_WIDTH)
		{
			*pixel_ptr++ = ceiling_c;
			x++;
		}
		y++;
	}
	// 2. SUELO (Mitad inferior)
	while (y < WIN_HEIGHT)
	{
		pixel_ptr = (int *)(grl->engine.screen_buff.addr
				+ (y * grl->engine.screen_buff.line_len));
		x = 0;
		while (x < WIN_WIDTH)
		{
			*pixel_ptr++ = floor_c;
			x++;
		}
		y++;
	}
}

static int	ft_get_texture_color(t_img *tex, int x, int y)
{
	char	*dst;

	// Protección de seguridad para texturas
	if (x < 0) x = 0;
	if (x >= tex->width) x = tex->width - 1;
	if (y < 0) y = 0;
	if (y >= tex->height) y = tex->height - 1;

	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}

static void	ft_draw_texture_stripe(t_grl *grl, t_ray *ray, int x)
{
	int	y;
	int	tex_y;
	int	tex_id;
	int	color;

	if (ray->side == 0)
		tex_id = 2 + (ray->ray_dir_x > 0); // 2=WE, 3=EA (según convención)
	else
		tex_id = 0 + (ray->ray_dir_y > 0); // 0=NO, 1=SO (según convención)

	// NOTA: Verifica si tus IDs coinciden con: 0=NO, 1=SO, 2=WE, 3=EA
	// Si ray_dir_x > 0 (mira al ESTE/EA), ID debe ser 3. 
	// Si ray_dir_x < 0 (mira al OESTE/WE), ID debe ser 2.
	// Ajusta la lógica aquí si es necesario.
	// Lógica actual:
	// side 0 (Vertical): dir_x > 0 -> id=3 (EA), dir_x < 0 -> id=2 (WE). OK.
	// side 1 (Horizontal): dir_y > 0 -> id=1 (SO), dir_y < 0 -> id=0 (NO). OK.

	ray->step = 1.0 * 64 / ray->line_height;
	ray->tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos & (64 - 1);
		ray->tex_pos += ray->step;
		color = ft_get_texture_color(&grl->engine.textures[tex_id],
				ray->tex_x, tex_y);
		ft_put_pixel(grl, x, y, color);
		y++;
	}
}

void	ft_raycast_walls(t_grl *grl)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		// ft_init_ray ahora está definida en engine_raycast.c
		// Asegúrate de tener el prototipo en el .h si no lo ves
		extern void ft_init_ray(t_ray *ray, t_grl *grl, int x);
		extern void ft_calc_step(t_ray *ray, t_grl *grl);
		extern void ft_perform_dda(t_ray *ray, t_grl *grl);
		extern void ft_calc_wall_height(t_ray *ray);
		extern void ft_calc_texture_x(t_ray *ray, t_grl *grl);

		ft_init_ray(&ray, grl, x);
		ft_calc_step(&ray, grl);
		ft_perform_dda(&ray, grl);
		ft_calc_wall_height(&ray);
		ft_calc_texture_x(&ray, grl);
		ft_draw_texture_stripe(grl, &ray, x);
		x++;
	}
}

int	ft_game_loop(t_grl *grl)
{
	double	dt;
	double	move_speed;
	double	rot_speed;

	dt = get_delta_time(grl);
	move_speed = 3.0 * dt;
	rot_speed = 2.0 * dt;

	if (grl->keys.w || grl->keys.s || grl->keys.a || grl->keys.d)
		ft_move_player_pro(grl, move_speed);
	if (grl->keys.right)
		ft_rotate_player_pro(grl, rot_speed);
	if (grl->keys.left)
		ft_rotate_player_pro(grl, -rot_speed);

	ft_render_floor_ceiling(grl);
	ft_raycast_walls(grl);
	mlx_put_image_to_window(grl->engine.mlx,
		grl->engine.win,
		grl->engine.screen_buff.img_ptr,
		0, 0);
	return (0);
}
