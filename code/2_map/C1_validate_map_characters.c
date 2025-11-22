#include "../../include/cub3D.h"

static int	ft_is_valid_map_char(char c);

// R3 - Validar que todos los caracteres del mapa sean válidos
void	ft_validate_map_characters(t_grl *grl)
{
	int	row;
	int	col;
	int	line_len;

	if (!grl || !grl->map_block)
		ft_ctrl_cleanUp(grl, "Map block missing", 1);
	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			ft_ctrl_cleanUp(grl, "Map line missing", 1);
		line_len = ft_strlen(grl->map_block[row]);
		col = 0;
		while (col < line_len)
		{
			if (!ft_is_valid_map_char(grl->map_block[row][col]))
				ft_ctrl_cleanUp(grl, "Invalid map character", 1);
			col++;
		}
		row++;
	}
}

int	ft_is_valid_map_char(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	if (c == ' ')
		return (1);
	return (0);
}

