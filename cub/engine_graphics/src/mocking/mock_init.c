#include "../include/cub3D.h"

/*
 Rellena la estructura t_game con un mapa falso y datos de jugador
 para probar el motor gráfico de forma aislada.
 */


 
void    ft_init_mock_data(t_game *game)
{
    // 1. Datos de texturas y colores (simulados)
    game->map.no_path = ft_strdup("./texturas/muro_norte.xpm");
    game->map.so_path = ft_strdup("./texturas/muro_sur.xpm");
    game->map.we_path = ft_strdup("./texturas/muro_oeste.xpm");
    game->map.ea_path = ft_strdup("./texturas/muro_este.xpm");
    game->map.floor_color = 0x888888; // Gris
    game->map.ceiling_color = 0x333333; // Gris oscuro

    // 2. Datos del mapa (un 5x5 simple, como en tu plan)
    game->map.map_h = 5;
    game->map.map_w = 5;
    game->map.grid = ft_split("11111\n10001\n10N01\n10001\n11111", '\n');
    if (!game->map.grid)
        ft_ctrl_cleanUp(game, "Malloc failed in mock_init", 0);

    // 3. Datos del jugador (basado en 'N' en 2,2)
    game->player.pos_x = 2.5;
    game->player.pos_y = 2.5;
    game->player.dir_x = 0.0;
    game->player.dir_y = -1.0;
    game->player.plane_x = 0.66;
    game->player.plane_y = 0.0;

    printf("✅ MOCK: Datos falsos cargados.\n");
}