/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhiguita <rhiguita@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 23:02:28 by rhiguita          #+#    #+#             */
/*   Updated: 2025/11/24 11:04:21 by rhiguita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	ft_load_single_texture(t_grl *grl, int id, char *path)
{
	if (!path)
		ft_ctrl_cleanUp(grl, "Error: Texture path is NULL", 1);
	grl->engine.textures[id].img_ptr = mlx_xpm_file_to_image(grl->engine.mlx,
			path, &grl->engine.textures[id].width,
			&grl->engine.textures[id].height);
	if (!grl->engine.textures[id].img_ptr)
	{
		printf("Error loading texture ID %d: %s\n", id, path);
		ft_ctrl_cleanUp(grl, "Error: mlx_xpm_file_to_image failed", 1);
	}
	grl->engine.textures[id].addr = mlx_get_data_addr(
			grl->engine.textures[id].img_ptr,
			&grl->engine.textures[id].bpp,
			&grl->engine.textures[id].line_len,
			&grl->engine.textures[id].endian);
}

//Carga las 4 texturas usando las rutas parseadas en grl->assets.
//Orden: NO(0), SO(1), WE(2), EA(3).
void	ft_load_textures(t_grl *grl)
{
	ft_load_single_texture(grl, 0, grl->assets.textures_path[HDR_NO]);
	ft_load_single_texture(grl, 1, grl->assets.textures_path[HDR_SO]);
	ft_load_single_texture(grl, 2, grl->assets.textures_path[HDR_WE]);
	ft_load_single_texture(grl, 3, grl->assets.textures_path[HDR_EA]);
	printf("✅ MOTOR: Texturas cargadas correctamente.\n");
}

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

void	ft_init_motor(t_grl *grl)
{
	grl->engine.mlx = mlx_init();
	if (!grl->engine.mlx)
		ft_ctrl_cleanUp(grl, "Error: mlx_init() failed", 1);
	grl->engine.win = mlx_new_window(grl->engine.mlx, WIN_WIDTH,
			WIN_HEIGHT, "cub3D");
	if (!grl->engine.win)
		ft_ctrl_cleanUp(grl, "Error: mlx_new_window() failed", 1);
	printf("✅ MOTOR: MLX y Ventana iniciados.\n");
	ft_init_screen_buffer(grl);
	ft_load_textures(grl);
}
