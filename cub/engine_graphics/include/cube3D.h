
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
// # include "../../minilibx-linux/mlx.h" // <-- Descomenta cuando instales MLX

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

// t_grl: El "cerebro" (¡Ahora con contenido!)
typedef struct s_grl
{
	t_mapdata	map;
	t_player	player;
	t_engine	engine;
	char		**raw_file;
}	t_grl;

// --- PROTOTIPOS ---

// ENGINE (Tu Módulo)
void	ft_init_mock_data(t_grl *grl); // FASE 1: Tu "mapa falso"

// CLEANUP (Importamos los de Álex para usarlos)
void	ft_ctrl_cleanUp(t_grl *grl, char *sterror, int exit_code);
void	ft_print_error(char *sterror);
void	ft_free(t_grl *grl);

#endif