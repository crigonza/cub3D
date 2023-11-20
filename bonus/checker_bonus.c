/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/20 19:14:44 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

int	check_player_duplicate(t_game *game)
{
	int	i;
	int	j;
	int	dup;

	i = 0;
	dup = 0;
	while (i < game->map.map_h)
	{
		j = 0;
		while (game->map.map_array[i][j])
		{
			if (game->map.map_array[i][j] == 'N'
				|| game->map.map_array[i][j] == 'S'
				|| game->map.map_array[i][j] == 'W'
				|| game->map.map_array[i][j] == 'E')
				dup++;
			j++;
		}
		i++;
	}
	if (dup == 1)
		return (1);
	return (0);
}

int	check_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.map_h)
	{
		j = 0;
		while (game->map.map_array[i][j])
		{
			if ((ft_strchr("WESN", game->map.map_array[i][j]) != NULL)
				&& check_map_point(game->map.map_array, i, j))
			{
				game->player.pos_x = j + 0.5;
				game->player.pos_y = i + 0.5;
				set_dir(&game->player, game->map.map_array[i][j]);
				game->player.speed = 0.03;
				game->player.rotate_speed = 0.03;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	check_colors(t_data *data, t_game *game)
{
	if (data->floor.red > 255 || data->floor.green > 255
		|| data->floor.blue > 255 || data->ceiling.red > 255
		|| data->ceiling.green > 255 || data->ceiling.blue > 255)
	{
		ft_putendl_fd("Error: invalid floor or ceiling rgb color.", 2);
		return (0);
	}
	if (data->floor.red == -1 || data->ceiling.red == -1)
	{
		ft_putendl_fd("Error: missing floor or ceiling color.", 2);
		return (0);
	}
	if (data->floor.red < 0 || data->floor.green < 0 || data->floor.blue < 0
		|| data->ceiling.red < 0 || data->ceiling.green < 0
		|| data->ceiling.blue < 0)
	{
		ft_putendl_fd("Error: invalid floor or ceiling rgb color.", 2);
		return (0);
	}
	game->textures.ceiling_color = get_rgba(data->ceiling.red,
			data->ceiling.green, data->ceiling.blue, 0xFF);
	game->textures.floor_color = get_rgba(data->floor.red, data->floor.green,
			data->floor.blue, 0xFF);
	return (1);
}

int	load_textures(t_data *data, t_game *game)
{
	t_texture	textures;
	int			fd[4];

	fd[0] = open(data->north, O_RDONLY);
	fd[1] = open(data->south, O_RDONLY);
	fd[2] = open(data->west, O_RDONLY);
	fd[3] = open(data->east, O_RDONLY);
	if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1)
	{
		ft_putendl_fd("Error: cant open texture file.", 2);
		return (0);
	}
	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
	close(fd[3]);
	textures.north = mlx_load_png(data->north);
	textures.south = mlx_load_png(data->south);
	textures.west = mlx_load_png(data->west);
	textures.east = mlx_load_png(data->east);
	game->textures = textures;
	return (1);
}

int	check_data(t_data *data, t_game *game)
{
	if (!data->north || !data->south || !data->west || !data->east)
	{
		ft_putendl_fd("Error: missing wall texture.", 2);
		return (0);
	}
	if (!load_textures(data, game) || !check_colors(data, game))
		return (0);
	if (!game->map.map_array[0])
	{
		ft_putendl_fd("Error: invalid map.", 2);
		return (0);
	}
	if (!check_player(game) || !check_player_duplicate(game))
	{
		ft_putendl_fd("Error: missing player start point.", 2);
		return (0);
	}
	if (!check_map(game->map))
	{
		ft_putendl_fd("Error: invalid map.", 2);
		return (0);
	}
	return (1);
}
