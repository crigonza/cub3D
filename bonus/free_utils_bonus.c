/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:04:06 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/14 13:52:03 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	game_over(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.map_h)
	{
		free(game->map.map_array[i]);
		i++;
	}
	free(game->map.map_array);
	mlx_delete_texture(game->textures.north);
	mlx_delete_texture(game->textures.south);
	mlx_delete_texture(game->textures.west);
	mlx_delete_texture(game->textures.east);
	if (game->bonus)
	{
		mlx_delete_texture(game->sprite.frame1);
		mlx_delete_texture(game->sprite.frame2);
		mlx_delete_texture(game->sprite.frame3);
		mlx_delete_texture(game->sprite.frame4);
	}
}

void	free_data(t_data *data)
{
	free(data->north);
	free(data->south);
	free(data->east);
	free(data->west);
}
