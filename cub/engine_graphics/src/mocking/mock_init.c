

// ¡¡Incluimos el .h de NUESTRO módulo!!
#include "../include/cube3D.h"

/**
 * @brief Rellena la estructura t_grl con un mapa falso y datos de jugador
 * para probar el motor gráfico de forma aislada.
 */
void    ft_init_mock_data(t_grl *grl)
{
    // 1. Datos de texturas y colores (simulados)
    grl->map.no_path = ft_strdup("./texturas/muro_norte.xpm");
    grl->map.so_path = ft_strdup("./texturas/muro_sur.xpm");
    grl->map.we_path = ft_strdup("./texturas/muro_oeste.xpm");
    grl->map.ea_path = ft_strdup("./texturas/muro_este.xpm");
    grl->map.floor_color = 0x888888; // Gris
    grl->map.ceiling_color = 0x333333; // Gris oscuro

    // 2. Datos del mapa (un 5x5 simple)
    grl->map.map_h = 5;
    grl->map.map_w = 5;
    grl->map.grid = ft_split("11111\n10001\n10N01\n10001\n11111", '\n');
    if (!grl->map.grid)
        ft_ctrl_cleanUp(grl, "Malloc failed in mock_init", 0);

    // 3. Datos del jugador (basado en 'N' en 2,2)
    grl->player.pos_x = 2.5;
    grl->player.pos_y = 2.5;
    grl->player.dir_x = 0.0;
    grl->player.dir_y = -1.0;
    grl->player.plane_x = 0.66;
    grl->player.plane_y = 0.0;

    printf("✅ MOCK: Datos falsos cargados.\n");
}