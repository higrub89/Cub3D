/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:02:01 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/22 23:02:20 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	ft_close_game(t_grl *grl)
{
	printf("Cerrando el juego correctamente...\n");
    // Llamada unificada a cleanUp (Codigo 0 = Exito)
	ft_ctrl_cleanUp(grl, NULL, 0);
	return (0);
}

int	ft_handle_keypress(int key, t_grl *grl)
{
	if (key == KEY_ESC)
		ft_close_game(grl);
	if (key == KEY_W)
		grl->keys.w = 1;
	if (key == KEY_S)
		grl->keys.s = 1;
	if (key == KEY_A)
		grl->keys.a = 1;
	if (key == KEY_D)
		grl->keys.d = 1;
	if (key == KEY_LEFT)
		grl->keys.left = 1;
	if (key == KEY_RIGHT)
		grl->keys.right = 1;
	return (0);
}

int	ft_handle_keyrelease(int key, t_grl *grl)
{
	if (key == KEY_W)
		grl->keys.w = 0;
	if (key == KEY_S)
		grl->keys.s = 0;
	if (key == KEY_A)
		grl->keys.a = 0;
	if (key == KEY_D)
		grl->keys.d = 0;
	if (key == KEY_LEFT)
		grl->keys.left = 0;
	if (key == KEY_RIGHT)
		grl->keys.right = 0;
	return (0);
}

void	ft_setup_hooks(t_grl *grl)
{
	mlx_hook(grl->engine.win, 2, 1L << 0, ft_handle_keypress, grl);
	mlx_hook(grl->engine.win, 3, 1L << 1, ft_handle_keyrelease, grl);
	mlx_hook(grl->engine.win, 17, 1L << 0, ft_close_game, grl);
	mlx_loop_hook(grl->engine.mlx, ft_game_loop, grl);
}
