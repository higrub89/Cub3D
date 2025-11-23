/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:03:23 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/22 23:04:43 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <sys/time.h>

double	get_delta_time(t_grl *grl)
{
	struct timeval	time;
	double			current_time;
	double			delta;

	gettimeofday(&time, NULL);
	current_time = time.tv_sec + (time.tv_usec / 1000000.0);
	if (grl->old_time == 0)
		grl->old_time = current_time;
	delta = current_time - grl->old_time;
	grl->old_time = current_time;
	return (delta);
}

void	ft_rotate_player_pro(t_grl *grl, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = grl->player.dir_x;
	grl->player.dir_x = grl->player.dir_x * cos(rot_speed)
		- grl->player.dir_y * sin(rot_speed);
	grl->player.dir_y = old_dir_x * sin(rot_speed)
		+ grl->player.dir_y * cos(rot_speed);
	old_plane_x = grl->player.plane_x;
	grl->player.plane_x = grl->player.plane_x * cos(rot_speed)
		- grl->player.plane_y * sin(rot_speed);
	grl->player.plane_y = old_plane_x * sin(rot_speed)
		+ grl->player.plane_y * cos(rot_speed);
}

static void	ft_apply_move(t_grl *grl, double move_x, double move_y)
{
	double	new_x;
	double	new_y;

    // Margen de colisión para no pegar el ojo a la pared (0.1)
    double margin = 0.1; 

	new_x = grl->player.pos_x + move_x;
	new_y = grl->player.pos_y + move_y;

    // Verificamos X (Deslizamiento) en map_block
	if (grl->map_block[(int)grl->player.pos_y][(int)(new_x + (move_x > 0 ? margin : -margin))] != '1')
		grl->player.pos_x = new_x;

    // Verificamos Y (Deslizamiento) en map_block
	if (grl->map_block[(int)(new_y + (move_y > 0 ? margin : -margin))][(int)grl->player.pos_x] != '1')
		grl->player.pos_y = new_y;
}

void	ft_move_player_pro(t_grl *grl, double speed)
{
	double	mx;
	double	my;

	mx = 0;
	my = 0;
	if (grl->keys.w)
	{
		mx += grl->player.dir_x;
		my += grl->player.dir_y;
	}
	if (grl->keys.s)
	{
		mx -= grl->player.dir_x;
		my -= grl->player.dir_y;
	}
	if (grl->keys.d)
	{
		mx += grl->player.plane_x;
		my += grl->player.plane_y;
	}
	if (grl->keys.a)
	{
		mx -= grl->player.plane_x;
		my -= grl->player.plane_y;
	}
	ft_apply_move(grl, mx * speed, my * speed);
}
