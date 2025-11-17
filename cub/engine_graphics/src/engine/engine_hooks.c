#include "../include/cube3D.h"

/**
 * @brief (FASE 2) La función de salida limpia.
 * Destruye todo lo de MLX y libera la memoria.
 */
int	ft_close_game(t_grl *grl)
{
	printf("Cerrando el juego...\n");
	
	// 1. Destruir el buffer de pantalla (FASE 3)
	if (grl->engine.screen_buff.img_ptr)
		mlx_destroy_image(grl->engine.mlx, grl->engine.screen_buff.img_ptr);
	
	// 2. (Aquí liberarías texturas cuando las carguemos)
	// for (int i = 0; i < 4; i++)
	//     if (grl->engine.textures[i].img_ptr)
	//         mlx_destroy_image(grl->engine.mlx, grl->engine.textures[i].img_ptr);

	// 3. Destruir la ventana y la conexión
	if (grl->engine.win)
		mlx_destroy_window(grl->engine.mlx, grl->engine.win);
	if (grl->engine.mlx)
	{
		mlx_destroy_display(grl->engine.mlx);
		free(grl->engine.mlx);
	}
	
	// 4. Liberar datos mock (rutas de texturas y mapa)
	ft_free_mock_data(grl);
	
	// 5. (Aquí llamarías a la función de Álex para liberar el parser)
	// ft_free(grl); 

	printf("¡Hasta luego!\n");
	exit(0);
	return (0);
}

/**
 * @brief (FASE 2) Manejador de pulsaciones de teclas.
 */
static int	ft_handle_keypress(int keycode, t_grl *grl)
{
	// Si se pulsa ESC, cerramos el juego
	if (keycode == KEY_ESC)
		ft_close_game(grl);

	// (Aquí irá la lógica de W, A, S, D y flechas)

	return (0);
}

/**
 * @brief (FASE 2) Configura todos los hooks (eventos) de MLX.
 */
void	ft_setup_hooks(t_grl *grl)
{
	// 1. Hook para cerrar con 'ESC'
	mlx_key_hook(grl->engine.win, ft_handle_keypress, grl);

	// 2. Hook para cerrar con la 'X' de la ventana
	// (17 = DestroyNotify)
	mlx_hook(grl->engine.win, 17, (1L << 0), ft_close_game, grl);

	// 3. Hook para el loop de renderizado (FASE 3)
	// Se ejecuta en cada frame antes de que MLX procese eventos
	mlx_loop_hook(grl->engine.mlx, ft_game_loop, grl);
}