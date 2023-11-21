/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:56:19 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/21 12:30:22 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*get_next_line(int fd)
{
	char	c;
	int		i;
	int		rd;
	char	*buffer;

	i = 0;
	rd = 0;
	buffer = malloc(sizeof(char) * 100000);
	rd = read(fd, &c, 1);
	while (rd > 0)
	{
		buffer[i++] = c;
		if (c == '\n')
			break ;
		rd = read(fd, &c, 1);
	}
	buffer[i] = '\0';
	if (rd == -1 || i == 0 || (!buffer[i - 1] && !rd))
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	check_map_ini(char *line)
{
	int	i;
	int	is_map;

	i = 0;
	is_map = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			is_map = 1;
		i++;
	}
	if (is_map)
		free(line);
	return (is_map);
}
