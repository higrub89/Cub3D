

// ¡¡Incluimos el .h de NUESTRO módulo!!
#include "../include/cube3D.h"

/**
 * @brief Rellena la estructura t_grl con un mapa falso y datos de jugador
 * para probar el motor gráfico de forma aislada.
 */
void    ft_init_mock_data(t_grl *grl)
{
    // 1. Datos de texturas y colores (simulados)
    grl->map.no_path = ft_strdup("assets/texturas/rough_wall.xpm");   // Norte
    grl->map.so_path = ft_strdup("assets/texturas/rough_wall.xpm");   // Sur
    grl->map.we_path = ft_strdup("assets/texturas/color_wall.xpm");  // Oeste
    grl->map.ea_path = ft_strdup("assets/texturas/color_wall.xpm"); // Este
    grl->map.floor_color = ft_rgb_to_hex(15, 15, 18);
    grl->map.ceiling_color = ft_rgb_to_hex(30, 32, 38);

  // 2. Datos del mapa (un 15x15 con obstáculos)
    grl->map.map_h = 15;
    grl->map.map_w = 15;
    grl->map.grid = ft_split(
        "111111111111111\n"
        "100000000000001\n"
        "101110011111001\n"
        "101000000001001\n"
        "101011111001001\n"
        "101010001001001\n"
        "100000000000001\n"
        "101110110010001\n"
        "101000010010001\n"
        "101000010011111\n"
        "100000000000001\n"
        "101111111010001\n"
        "100000000010001\n"
        "100N00000000001\n"
        "111111111111111", '\n');

    if (!grl->map.grid)
        ft_ctrl_cleanUp(grl, "Malloc failed in mock_init", 0);

// 3. Datos del jugador (Actualizado para este mapa)
    // Posición (3.5, 13.5) corresponde a la 'N' en la penúltima fila
    grl->player.pos_x = 3.5;
    grl->player.pos_y = 13.5;
    grl->player.dir_x = 0.0;
    grl->player.dir_y = -1.0; // Mirando al Norte (hacia arriba en el mapa)
    grl->player.plane_x = 0.66;
    grl->player.plane_y = 0.0;

    printf("✅ MOCK: Datos falsos cargados.\n");
}

/**
 * @brief Libera toda la memoria asignada por ft_init_mock_data().
 * Debe ser llamada antes de cerrar el programa para evitar leaks.
 */
void	ft_free_mock_data(t_grl *grl)
{
	int	i;

	// 1. Liberar las 4 rutas de texturas mockeadas
	if (grl->map.no_path)
		free(grl->map.no_path);
	if (grl->map.so_path)
		free(grl->map.so_path);
	if (grl->map.we_path)
		free(grl->map.we_path);
	if (grl->map.ea_path)
		free(grl->map.ea_path);
	
	// 2. Liberar el mapa mock (grid creado con ft_split)
	if (grl->map.grid)
	{
		i = 0;
		while (grl->map.grid[i])
			free(grl->map.grid[i++]);
		free(grl->map.grid);
		grl->map.grid = NULL;
	}
	
	printf("✅ MOCK: Datos mock liberados.\n");
}
