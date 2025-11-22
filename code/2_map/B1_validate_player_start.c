#include "../../include/cub3D.h"

static int	ft_count_player_positions(t_grl *grl);
static int	ft_is_player_char(char c);

// R2 - Validar posición inicial única del jugador
void	ft_validate_player_start(t_grl *grl)
{
	int	count;

	if (!grl || !grl->map_block)
		ft_ctrl_cleanUp(grl, "Map block missing", 1);
	count = ft_count_player_positions(grl);
	if (count == 0)
		ft_ctrl_cleanUp(grl, "Player start position missing", 1);
	if (count > 1)
		ft_ctrl_cleanUp(grl, "Multiple player start positions", 1);
}

int	ft_count_player_positions(t_grl *grl)
{
	int	row;
	int	col;
	int	count;
	int	line_len;

	if (!grl->map_block)
		return (0);
	count = 0;
	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			return (0);
		line_len = ft_strlen(grl->map_block[row]);
		col = 0;
		while (col < line_len)
		{
			if (ft_is_player_char(grl->map_block[row][col]))
				count++;
			col++;
		}
		row++;
	}
	return (count);
}

int	ft_is_player_char(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

