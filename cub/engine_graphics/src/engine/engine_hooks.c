
#include "../../include/cube3D.h"

#define MOVE_SPEED 0.1
#define ROT_SPEED 0.1

int	ft_close_game(t_grl *grl)
{
	printf("Cerrando el juego...\n");
	if (grl->engine.screen_buff.img_ptr)
		mlx_destroy_image(grl->engine.mlx, grl->engine.screen_buff.img_ptr);
	if (grl->engine.win)
		mlx_destroy_window(grl->engine.mlx, grl->engine.win);
	if (grl->engine.mlx)
	{
		mlx_destroy_display(grl->engine.mlx);
		free(grl->engine.mlx);
	}
	ft_free_mock_data(grl);
	exit(0);
	return (0);
}

static void	ft_rotate_player(t_grl *grl, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = grl->player.dir_x;
	grl->player.dir_x = grl->player.dir_x * cos(rot_speed)
		- grl->player.dir_y * sin(rot_speed);
	grl->player.dir_y = old_dir_x * sin(rot_speed)
		+ grl->player.dir_y * cos(rot_speed);
	old_plane_x = grl->player.plane_x;
	grl->player.plane_x = grl->player.plane_x * cos(rot_speed)
		- grl->player.plane_y * sin(rot_speed);
	grl->player.plane_y = old_plane_x * sin(rot_speed)
		+ grl->player.plane_y * cos(rot_speed);
}

static void	ft_move_player(t_grl *grl, double move_x, double move_y)
{
	int		map_x;
	int		map_y;

	map_x = (int)(grl->player.pos_x + move_x);
	map_y = (int)(grl->player.pos_y);
	if (grl->map.grid[map_y][map_x] != '1')
		grl->player.pos_x += move_x;
	map_x = (int)(grl->player.pos_x);
	map_y = (int)(grl->player.pos_y + move_y);
	if (grl->map.grid[map_y][map_x] != '1')
		grl->player.pos_y += move_y;
}

static int	ft_handle_keypress(int key, t_grl *grl)
{
	if (key == KEY_ESC)
		ft_close_game(grl);
	if (key == KEY_W)
		ft_move_player(grl, grl->player.dir_x * MOVE_SPEED,
			grl->player.dir_y * MOVE_SPEED);
	if (key == KEY_S)
		ft_move_player(grl, -grl->player.dir_x * MOVE_SPEED,
			-grl->player.dir_y * MOVE_SPEED);
	if (key == KEY_A)
		ft_move_player(grl, grl->player.dir_y * MOVE_SPEED,
			-grl->player.dir_x * MOVE_SPEED);
	if (key == KEY_D)
		ft_move_player(grl, -grl->player.dir_y * MOVE_SPEED,
			grl->player.dir_x * MOVE_SPEED);
	if (key == KEY_RIGHT)
		ft_rotate_player(grl, ROT_SPEED);
	if (key == KEY_LEFT)
		ft_rotate_player(grl, -ROT_SPEED);
	return (0);
}

void	ft_setup_hooks(t_grl *grl)
{
	mlx_key_hook(grl->engine.win, ft_handle_keypress, grl);
	mlx_hook(grl->engine.win, 17, (1L << 0), ft_close_game, grl);
	mlx_loop_hook(grl->engine.mlx, ft_game_loop, grl);
}
