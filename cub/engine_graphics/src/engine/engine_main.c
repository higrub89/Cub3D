#include "../include/cube3D.h"

int main(void)
{
    t_grl  grl;

    ft_bzero(&grl, sizeof(t_grl));

    // 1. Rellenar con datos falsos (Mockup)
    ft_init_mock_data(&grl);

    // 2. Iniciar el motor (FASE 1)
    ft_init_motor(&grl);

	// 3. Configurar eventos (FASE 2)
	ft_setup_hooks(&grl);

    // 4. Iniciar el bucle del juego
	printf("Iniciando mlx_loop... (Pulsa ESC para salir)\n");
    mlx_loop(grl.engine.mlx);
    
    return (0);
}