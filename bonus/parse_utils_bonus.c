/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:54:17 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/15 19:19:46 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	spaces_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	*get_path(char *line)
{
	char	*path;
	int		i;
	int		j;

	i = 3;
	j = 0;
	path = (char *)malloc(sizeof(char) * (ft_strlen(line) - 3));
	while (line[i] != '\n')
	{
		path[j] = line[i];
		j++;
		i++;
	}
	path[j] = '\0';
	return (path);
}

t_color	get_color(char *rgb)
{
	char	**rgb_split;
	t_color	color;
	int		i;

	i = 0;
	rgb_split = ft_split(rgb, ',');
	color.red = ft_atoi(rgb_split[0]);
	color.green = ft_atoi(rgb_split[1]);
	color.blue = ft_atoi(rgb_split[2]);
	if (rgb_split != NULL)
	{
		while (rgb_split[i])
		{
			free(rgb_split[i]);
			i++;
		}
		free(rgb_split);
	}
	free(rgb);
	return (color);
}

void	set_plane(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	else if (dir == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	else if (dir == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
	else if (dir == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
}

void	set_dir(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	else if (dir == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (dir == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
	else if (dir == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	set_plane(player, dir);
}
