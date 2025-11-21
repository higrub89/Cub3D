/* En engine_graphics/include/cube3D.h */
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

// 1. t_img (Componente básico, debe ir primero o antes de usarse)
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

// 2. t_keys (Componente básico)
typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
    int left;
    int right;
}   t_keys;

// 3. t_mapdata (Componente básico)
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

// 4. t_player (Componente básico)
typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x;
    double  dir_y;
    double  plane_x;
    double  plane_y;
}   t_player;

// 5. t_ray (Usa solo tipos primitivos, puede ir aquí)
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
    
    // --- NUEVO PARA TEXTURAS ---
    double  wall_x;     // Punto exacto del impacto en el muro (0.0 a 1.0)
    int     tex_x;      // Coordenada X en la textura
    double  step;       // Cuanto avanzar en la textura por pixel de pantalla
    double  tex_pos;    // Posición actual en la textura
}   t_ray;

// 6. t_engine (Usa t_img, por eso va DESPUÉS de t_img)
typedef struct s_engine
{
    void    *mlx;
    void    *win;
    t_img   screen_buff;
    t_img   textures[4];
}   t_engine;

// 7. t_grl (Usa todas las anteriores, va AL FINAL)
typedef struct s_grl
{
    t_mapdata   map;
    t_player    player;
    t_engine    engine;
    t_keys      keys;       // Estado del teclado
    double      old_time;   // Para calcular Delta Time
    char        **raw_file;
}   t_grl;

// --- PROTOTIPOS DE FUNCIONES ---

// src/mocking/mock_init.c
void    ft_init_mock_data(t_grl *grl);
void    ft_free_mock_data(t_grl *grl);

// src/engine/engine_init.c
void    ft_init_motor(t_grl *grl);
void    ft_load_textures(t_grl *grl);

// src/engine/engine_hooks.c
void    ft_setup_hooks(t_grl *grl);
int     ft_handle_keypress(int key, t_grl *grl);
int     ft_handle_keyrelease(int key, t_grl *grl);
int     ft_close_game(t_grl *grl);

// src/engine/engine_movement.c
double  get_delta_time(t_grl *grl);
void    ft_rotate_player_pro(t_grl *grl, double rot_speed);
void    ft_move_player_pro(t_grl *grl, double move_speed);

// src/engine/engine_render.c
void    ft_init_screen_buffer(t_grl *grl);
void    ft_put_pixel(t_grl *grl, int x, int y, int color);
void    ft_raycast_walls(t_grl *grl);
int     ft_game_loop(t_grl *grl);
int     ft_rgb_to_hex(int r, int g, int b);

// src/engine/engine_raycast.c
void    ft_init_ray(t_ray *ray, t_grl *grl, int x);
void    ft_calc_step(t_ray *ray, t_grl *grl);
void    ft_perform_dda(t_ray *ray, t_grl *grl);
void    ft_calc_wall_height(t_ray *ray);
void    ft_calc_texture_x(t_ray *ray, t_grl *grl);

// code/cleanUp/cleanUp.c
void    ft_ctrl_cleanUp(t_grl *grl, char *sterror, int exit_code);
void    ft_print_error(char *sterror);
void    ft_free(t_grl *grl);

// EXTRAS
void imprimir_vector(char **v);

#endif