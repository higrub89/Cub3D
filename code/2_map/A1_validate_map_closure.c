#include "../../include/cub3D.h"

static void	ft_validate_map_borders(t_grl *grl);
static int	ft_is_border_cell(t_grl *grl, int row, int col, int line_len);
static void	ft_validate_border_cell(t_grl *grl, int row, int col);

// R1 - Validar cierre del mapa por paredes
void	ft_validate_map_closure(t_grl *grl)
{
	if (!grl || !grl->map_block)
		ft_ctrl_cleanUp(grl, "Map block missing", 1);
	ft_validate_map_borders(grl);
	ft_validate_internal_spaces(grl);
}

void	ft_validate_map_borders(t_grl *grl)
{
	int	row;
	int	col;
	int	line_len;

	if (!grl->map_block || grl->map_height <= 0)
		ft_ctrl_cleanUp(grl, "Invalid map dimensions", 1);
	row = 0;
	while (row < grl->map_height)
	{
		if (!grl->map_block[row])
			ft_ctrl_cleanUp(grl, "Map line missing", 1);
		line_len = ft_strlen(grl->map_block[row]);
		col = 0;
		while (col < line_len)
		{
			if (ft_is_border_cell(grl, row, col, line_len))
				ft_validate_border_cell(grl, row, col);
			col++;
		}
		row++;
	}
}

int	ft_is_border_cell(t_grl *grl, int row, int col, int line_len)
{
	if (row == 0 || row == grl->map_height - 1)
		return (1);
	if (col == 0 || col == line_len - 1)
		return (1);
	return (0);
}

void	ft_validate_border_cell(t_grl *grl, int row, int col)
{
	if (grl->map_block[row][col] != '1'
		&& grl->map_block[row][col] != ' ')
		ft_ctrl_cleanUp(grl, "Map borders not closed", 1);
}
