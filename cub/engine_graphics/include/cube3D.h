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
// --- ¡¡ACTUALIZADO!! Descomentamos MLX ---
# include "../../minilibx-linux/mlx.h" // <-- ¡IMPORTANTE!

// --- CONFIGURACIÓN ---
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

// --- ¡¡NUEVO!! Keycodes de Linux ---
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

// ... (todas tus structs t_mapdata, t_player, t_img, t_engine, t_grl) ...
// (Asegúrate de que t_grl reemplaza a t_game)
typedef struct s_mapdata
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	char	**grid;
	int		map_w;
	int		map_h;
}	t_mapdata;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_engine
{
	void	*mlx;
	void	*win;
	t_img	screen_buff;
	t_img	textures[4];
}	t_engine;

typedef struct s_grl
{
	t_mapdata	map;
	t_player	player;
	t_engine	engine;
	char		**raw_file;
}	t_grl;

// --- PROTOTIPOS ---

// ENGINE (Tu Módulo)
void	ft_init_mock_data(t_grl *grl); // FASE 1
void	ft_init_motor(t_grl *grl);     // FASE 1
void	ft_setup_hooks(t_grl *grl);    // FASE 2
int		ft_game_loop(t_grl *grl);      // FASE 3
int		ft_close_game(t_grl *grl);   // FASE 2

// CLEANUP (Módulo de Álex)
void	ft_ctrl_cleanUp(t_grl *grl, char *sterror, int exit_code);
void	ft_print_error(char *sterror);
void	ft_free(t_grl *grl);

#endif