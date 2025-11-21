/* ************************************************************************** */
/* */
/* engine_init.c                                       :::      ::::::::    */
/* By: Rubén <cub3D>                                 :+:      :+:    :+:    */
/* +:+ +:+         +:+      */
/* Created: 2025/02/20 12:00:00 by Rubén             #+#    #+#             */
/* Updated: 2025/02/20 12:00:00 by Rubén            ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../../include/cube3D.h"

static void	ft_load_single_texture(t_grl *grl, int id, char *path)
{
	grl->engine.textures[id].img_ptr = mlx_xpm_file_to_image(grl->engine.mlx,
			path, &grl->engine.textures[id].width,
			&grl->engine.textures[id].height);
	if (!grl->engine.textures[id].img_ptr)
	{
		printf("Error cargando textura: %s\n", path);
		ft_ctrl_cleanUp(grl, "Fallo carga texturas", 1);
	}
	grl->engine.textures[id].addr = mlx_get_data_addr(
			grl->engine.textures[id].img_ptr,
			&grl->engine.textures[id].bpp,
			&grl->engine.textures[id].line_len,
			&grl->engine.textures[id].endian);
}

void	ft_load_textures(t_grl *grl)
{
    // Cargamos las texturas en el orden: NO, SO, WE, EA
    // Asegúrate de que en mock_init.c las rutas sean correctas
	ft_load_single_texture(grl, 0, grl->map.no_path);
	ft_load_single_texture(grl, 1, grl->map.so_path);
	ft_load_single_texture(grl, 2, grl->map.we_path);
	ft_load_single_texture(grl, 3, grl->map.ea_path);
	printf("✅ MOTOR: Texturas cargadas correctamente.\n");
}

void	ft_init_motor(t_grl *grl)
{
	grl->engine.mlx = mlx_init();
	if (!grl->engine.mlx)
		ft_ctrl_cleanUp(grl, "Error: mlx_init() falló", 1);
	grl->engine.win = mlx_new_window(grl->engine.mlx, WIN_WIDTH,
			WIN_HEIGHT, "cub3D");
	if (!grl->engine.win)
		ft_ctrl_cleanUp(grl, "Error: mlx_new_window() falló", 1);
	printf("✅ MOTOR: MLX y Ventana iniciados.\n");
	ft_init_screen_buffer(grl);
	ft_load_textures(grl); // <--- ¡AÑADE ESTA LLAMADA!
}