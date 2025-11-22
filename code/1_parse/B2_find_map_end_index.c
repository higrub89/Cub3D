#include "../../include/cub3D.h"

void	ft_guard_against_map_gap(t_grl *grl, char **lines, int idx)
{
	if (!lines)
		ft_ctrl_cleanUp(grl, "Lines array missing", 1);
	while (lines[idx] && ft_is_line_empty(lines[idx]))
		idx++;
	if (lines[idx] && ft_is_map_line(lines[idx]))
		ft_ctrl_cleanUp(grl, "Map has gaps", 1);
}

void	ft_process_header_line(t_grl *grl, char *line)
{
	int		id;
	char	*value;

	id = ft_extract_header(line, &value);
	if (id < 0)
		ft_ctrl_cleanUp(grl, "Unknown header identifier", 1);
	if (id <= HDR_EA)
		ft_store_texture(grl, id, value);
	else
		ft_store_color(grl, id, value);
}

int	ft_extract_header(char *line, char **value)
{
	static const char	*tokens[HDR_TOTAL] = {
		"NO", "SO", "WE", "EA", "F", "C"};
	static const int	lengths[HDR_TOTAL] = {2, 2, 2, 2, 1, 1};
	int					idx;

	if (!line || !value)
		return (-1);
	while (*line == ' ' || *line == '\t')
		line++;
	idx = 0;
	while (idx < HDR_TOTAL)
	{
		if (!ft_strncmp(line, tokens[idx], lengths[idx]) &&
			(line[lengths[idx]] == ' ' || line[lengths[idx]] == '\t'))
		{
			line += lengths[idx];
			while (*line == ' ' || *line == '\t')
				line++;
			*value = line;
			return (idx);
		}
		idx++;
	}
	return (-1);
}

void	ft_store_texture(t_grl *grl, int idx, char *value)
{
	if (!value || *value == '\0')
		ft_ctrl_cleanUp(grl, "Texture path missing", 1);
	if (grl->assets.textures_path[idx])
		ft_ctrl_cleanUp(grl, "Texture duplicated", 1);
	grl->assets.textures_path[idx] = value;
	grl->assets.headers_mask |= (1 << idx);
}

void	ft_store_color(t_grl *grl, int idx, char *value)
{
	int	color_idx;

	if (!value || *value == '\0')
		ft_ctrl_cleanUp(grl, "Color value missing", 1);
	color_idx = idx - HDR_F;
	if (color_idx < 0 || color_idx > 1)
		ft_ctrl_cleanUp(grl, "Color index error", 1);
	if (grl->assets.colors[color_idx])
		ft_ctrl_cleanUp(grl, "Color duplicated", 1);
	grl->assets.colors[color_idx] = value;
	grl->assets.headers_mask |= (1 << idx);
}
