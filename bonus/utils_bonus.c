/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:56:19 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/14 13:52:42 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	check_bonus(char *path, t_game *game)
{
	char	*tmp;

	tmp = ft_strnstr(path, "bonus.cub", ft_strlen(path));
	if (tmp == NULL)
		game->bonus = 0;
	else
		game->bonus = 1;
}

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
