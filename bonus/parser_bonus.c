/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:33:16 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/14 13:52:36 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	map_data(t_data *data, int fd, int lines)
{
	char	*line;
	int		map_len;

	line = NULL;
	map_len = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!spaces_line(line))
			map_len++;
		else
			lines++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	data->map_lines = map_len;
	data->map_start = lines;
}

int	is_valid_color(char *line)
{
	int	i;
	int	s;

	i = 2;
	s = 0;
	while (line[i] && line[i] != '\n')
	{
		if ((line[i] < '0' || line[i] > '9') && line[i] != 32)
		{
			if (line[i] == ',')
				s++;
			else
				return (0);
		}
		i++;
	}
	if (s != 2)
		return (0);
	return (1);
}

void	parse_colors(t_data *data, int fd, int lines)
{
	char	*line;

	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "F ", 2))
		{
			if (is_valid_color(line))
				data->floor = get_color(ft_substr(line, 2, ft_strlen(line)));
		}
		if (!ft_strncmp(line, "C ", 2))
		{
			if (is_valid_color(line))
				data->ceiling = get_color(ft_substr(line, 2, ft_strlen(line)));
		}
		free(line);
		lines++;
		if (data->ceiling.red != -1)
			break ;
		line = get_next_line(fd);
	}
	map_data(data, fd, lines);
}

void	parse_textures(t_data *data, int fd)
{
	char	*line;
	int		lines;

	lines = 0;
	line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "NO ", 3) && data->north == NULL)
			data->north = get_path(line);
		if (!ft_strncmp(line, "SO ", 3) && data->north != NULL)
			data->south = get_path(line);
		if (!ft_strncmp(line, "WE ", 3) && data->south != NULL)
			data->west = get_path(line);
		if (!ft_strncmp(line, "EA ", 3) && data->west != NULL)
			data->east = get_path(line);
		free(line);
		lines++;
		if (data->north && data->south && data->west && data->east)
			break ;
		line = get_next_line(fd);
	}
	parse_colors(data, fd, lines);
}

void	parse_map(t_data *data, int fd, t_game *game)
{
	int		i;
	int		len;
	int		width;
	char	*line;

	i = 0;
	width = 0;
	line = NULL;
	game->map.map_h = data->map_lines;
	game->map.map_array = (char **)malloc(sizeof(char *) * data->map_lines);
	while (i < data->map_lines)
	{
		line = get_next_line(fd);
		game->map.map_array[i] = ft_strdup(line);
		len = ft_strlen(line);
		if (width < len)
			width = len;
		free(line);
		i++;
	}
	game->map.map_w = width;
}