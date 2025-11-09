#ifndef CUB3D_H
# define CUB3D_H

// Incluimos libft (la ruta sube 2 niveles)
# include "../../libft/include/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
// Incluye la minilibX 
// # include "../../minilibx-linux/mlx.h" 

// --- CONFIGURACIÓN ---
# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

// --- ESTRUCTURAS DEL "CONTRATO" ---

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

// t_game: El "cerebro" (reemplaza a t_grl)
typedef struct s_game
{
	t_mapdata	map;
	t_player	player;
	t_engine	engine;
	char		**raw_file; // El `char **lines` de Álex
}	t_game;

// --- PROTOTIPOS ---

// ENGINE (Tu Módulo)
void	ft_init_mock_data(t_game *game); // FASE 1: Tu "mapa falso"
// (Añadiremos más prototipos aquí: ft_init_motor, ft_setup_hooks...)

// PARSER (Módulo de Álex)
void	ft_ctrl_parse(t_game *game, const char *map_file);
// ... (puedes copiar el resto de prototipos de su include/cub3D.h) ...

// CLEANUP (Módulo de Álex)
void	ft_ctrl_cleanUp(t_game *game, char *sterror, int exit_code);
void	ft_print_error(char *sterror);
void	ft_free(t_game *game);

#endif