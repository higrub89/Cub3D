/* En engine_graphics/include/cub3D.h */
#ifndef CUB3D_H
# define CUB3D_H

# include "../../libft/include/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include "../../minilibx-linux/mlx.h" 

// --- CONFIGURACIÓN ---
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

// --- KEYCODES (Linux / X11) ---
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// --- ESTRUCTURAS ---

typedef struct s_mapdata
{
    char    *no_path;
    char    *so_path;
    char    *we_path;
    char    *ea_path;
    int     floor_color;
    int     ceiling_color;
    char    **grid;
    int     map_w;
    int     map_h;
}   t_mapdata;

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}   t_player;

typedef struct s_img
{
    void    *img_ptr;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_img;

// Estructura para el Raycasting (DDA)
typedef struct s_ray
{
    double  camera_x;
    double  ray_dir_x;
    double  ray_dir_y;
    int     map_x;
    int     map_y;
    double  side_dist_x;
    double  side_dist_y;
    double  delta_dist_x;
    double  delta_dist_y;
    double  perp_wall_dist;
    int     step_x;
    int     step_y;
    int     hit;
    int     side;       // 0 = Vertical, 1 = Horizontal
    int     line_height;
    int     draw_start;
    int     draw_end;
    int     color;
}   t_ray;

typedef struct s_engine
{
    void    *mlx;
    void    *win;
    t_img   screen_buff;
    t_img   textures[4];
}   t_engine;

typedef struct s_grl
{
    t_mapdata   map;
    t_player    player;
    t_engine    engine;
    char        **raw_file;
}   t_grl;

// --- PROTOTIPOS DE FUNCIONES ---

// src/mocking/mock_init.c (Datos falsos para pruebas)
void    ft_init_mock_data(t_grl *grl);
void    ft_free_mock_data(t_grl *grl);

// src/engine/engine_init.c
void    ft_init_motor(t_grl *grl);

// src/engine/engine_hooks.c
void    ft_setup_hooks(t_grl *grl);
int     ft_close_game(t_grl *grl);

// src/engine/engine_render.c
void    ft_init_screen_buffer(t_grl *grl);
void    ft_put_pixel(t_grl *grl, int x, int y, int color);
void    ft_raycast_walls(t_grl *grl);
int     ft_game_loop(t_grl *grl);

// src/engine/engine_raycast.c (Cálculos DDA)
void    ft_init_ray(t_ray *ray, t_grl *grl, int x);
void    ft_calc_step(t_ray *ray, t_grl *grl);
void    ft_perform_dda(t_ray *ray, t_grl *grl);
void    ft_calc_wall_height(t_ray *ray);
void    ft_get_wall_color(t_ray *ray);

// code/cleanUp/cleanUp.c (Módulo de limpieza)
void    ft_ctrl_cleanUp(t_grl *grl, char *sterror, int exit_code);
void    ft_print_error(char *sterror);
void    ft_free(t_grl *grl);

#endif