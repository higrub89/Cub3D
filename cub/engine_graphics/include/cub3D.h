/* include/cub3D.h */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx-linux/mlx.h" // Ajusta esta ruta si es necesario

// Dimensiones de la ventana
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

// Estructura para el mapa (lo que te dará Álex)
typedef struct s_map
{
    char    **grid;     // La matriz del mapa: '1' pared, '0' suelo
    int     width;      // Ancho total del mapa
    int     height;     // Alto total del mapa
    // Colores y texturas vendrán luego
}   t_map;

// Estructura del jugador (necesaria para el raycasting)
typedef struct s_player
{
    double  pos_x;      // Posición exacta X
    double  pos_y;      // Posición exacta Y
    double  dir_x;      // Vector de dirección X
    double  dir_y;      // Vector de dirección Y
    double  plane_x;    // Vector del plano de cámara X (para el FOV)
    double  plane_y;    // Vector del plano de cámara Y
}   t_player;

// Estructura principal del juego
typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_map       mapinfo;
    t_player    player;
}   t_game;

// Prototipo de tu función mock
void    init_mock_map(t_game *game);

#endif
