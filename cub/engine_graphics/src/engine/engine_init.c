#include "../include/cube3D.h"

/**
 * @brief (FASE 1) Inicia la conexión con MLX y crea la ventana.
 */
void	ft_init_motor(t_grl *grl)
{
	// 1. Conectar con el servidor gráfico
	grl->engine.mlx = mlx_init();
	if (!grl->engine.mlx)
		ft_ctrl_cleanUp(grl, "Error: mlx_init() falló", 1);

	// 2. Crear la ventana
	grl->engine.win = mlx_new_window(grl->engine.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!grl->engine.win)
		ft_ctrl_cleanUp(grl, "Error: mlx_new_window() falló", 1);

	printf("✅ MOTOR: MLX y Ventana iniciados.\n");
	
	// (Próximo paso: crear el buffer de pantalla (screen_buff) aquí)
}