/* ************************************************************************** */
/* */
/* engine_movement.c                                   :::      ::::::::    */
/* By: Rubén <cub3D>                                 :+:      :+:    :+:    */
/* +:+ +:+         +:+      */
/* Created: 2025/02/20 12:00:00 by Rubén             #+#    #+#             */
/* Updated: 2025/02/20 12:00:00 by Rubén            ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../../include/cube3D.h"
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

	new_x = grl->player.pos_x + move_x;
	new_y = grl->player.pos_y + move_y;
	if (grl->map.grid[(int)grl->player.pos_y][(int)new_x] != '1')
		grl->player.pos_x = new_x;
	if (grl->map.grid[(int)new_y][(int)grl->player.pos_x] != '1')
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