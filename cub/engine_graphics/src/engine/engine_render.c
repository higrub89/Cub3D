/* ************************************************************************** */
/* */
/* engine_render.c                                     :::      ::::::::    */
/* By: Rubén <cub3D>                                 :+:      :+:    :+:    */
/* +:+ +:+         +:+      */
/* Created: 2025/02/20 12:05:00 by Rubén             #+#    #+#             */
/* Updated: 2025/02/20 12:05:00 by Rubén            ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../../include/cube3D.h"

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

static int	ft_get_texture_color(t_img *tex, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
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
		tex_id = 2 + (ray->ray_dir_x > 0);
	else
		tex_id = 0 + (ray->ray_dir_y > 0);
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

// ft_init_screen_buffer y ft_render_floor_ceiling se han movido
// a otro archivo para respetar el limite de 5 funciones por archivo
// si las necesitas aqui, dilo y reestructuramos.
// POR AHORA ASUMO QUE LAS MOVEREMOS A engine_init.c O CREAREMOS engine_utils.c

// PARA QUE COMPILE AHORA MISMO CON LO QUE TIENES, 
// PEGA AQUI DE NUEVO ft_init_screen_buffer Y ft_render_floor_ceiling
// (Te las pongo abajo para copiar y pegar todo junto)

void	ft_init_screen_buffer(t_grl *grl)
{
	grl->engine.screen_buff.img_ptr = mlx_new_image(grl->engine.mlx,
			WIN_WIDTH, WIN_HEIGHT);
	if (!grl->engine.screen_buff.img_ptr)
		ft_ctrl_cleanUp(grl, "Error: mlx_new_image() failed", 1);
	grl->engine.screen_buff.addr = mlx_get_data_addr(
			grl->engine.screen_buff.img_ptr,
			&grl->engine.screen_buff.bpp,
			&grl->engine.screen_buff.line_len,
			&grl->engine.screen_buff.endian);
	grl->engine.screen_buff.width = WIN_WIDTH;
	grl->engine.screen_buff.height = WIN_HEIGHT;
	printf("✅ RENDER: Screen buffer initialized (%dx%d).\n",
		WIN_WIDTH, WIN_HEIGHT);
}

static void	ft_render_floor_ceiling(t_grl *grl)
{
	int	x;
	int	y;
	int	half;

	half = WIN_HEIGHT / 2;
	y = -1;
	while (++y < half)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			ft_put_pixel(grl, x, y, grl->map.ceiling_color);
	}
	while (y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
			ft_put_pixel(grl, x, y, grl->map.floor_color);
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
	ft_render_floor_ceiling(grl);
	ft_raycast_walls(grl);
	mlx_put_image_to_window(grl->engine.mlx,
		grl->engine.win,
		grl->engine.screen_buff.img_ptr,
		0, 0);
	return (0);
}