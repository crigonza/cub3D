/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:39:33 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/20 19:22:37 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_file_colors(int *tex_and_col, char *file)
{
	char	*line;
	int		fd;

	tex_and_col[4] = 0;
	tex_and_col[5] = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "C ", 2))
			tex_and_col[4]++;
		if (!ft_strncmp(line, "F ", 2))
			tex_and_col[5]++;
		free (line);
		line = get_next_line(fd);
	}
	close (fd);
	if (tex_and_col[0] == 1 && tex_and_col[1] == 1 && tex_and_col[2] == 1
		&& tex_and_col[3] == 1 && tex_and_col[4] == 1 && tex_and_col[5] == 1)
		return (1);
	else
		ft_putendl_fd("Error: duplicated texture or color.", 2);
	return (0);
}

int	check_file_tex(char *file)
{
	int		tex_and_col[6];
	int		fd;
	char	*line;

	tex_and_col[0] = 0;
	tex_and_col[1] = 0;
	tex_and_col[2] = 0;
	tex_and_col[3] = 0;
	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_strncmp(line, "NO ", 3))
			tex_and_col[0]++;
		if (!ft_strncmp(line, "SO ", 3))
			tex_and_col[1]++;
		if (!ft_strncmp(line, "WE ", 3))
			tex_and_col[2]++;
		if (!ft_strncmp(line, "EA ", 3))
			tex_and_col[3]++;
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (check_file_colors(tex_and_col, file));
}

int	check_args(int argc, char **argv)
{
	char	*tmp;
	int		fd;

	if (argc != 2)
	{
		ft_putendl_fd("Error: invalid arguments number.", 2);
		return (0);
	}
	tmp = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
	if (tmp == NULL)
	{
		ft_putendl_fd("Error: invalid map archive.", 2);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putendl_fd("Error: invalid archive format.", 2);
		close(fd);
		return (0);
	}
	if (!check_file_tex(argv[1]))
		return (0);
	close(fd);
	return (1);
}
