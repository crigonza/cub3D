/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:04:06 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/27 21:07:50 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    game_over(t_game *game)
{
    int i;

    i = 0;
    while (game->map.map_array[i])
    {
        free (game->map.map_array[i]);
        i++;
    }
    mlx_delete_texture(game->textures.north);
    mlx_delete_texture(game->textures.south);
    mlx_delete_texture(game->textures.west);
    mlx_delete_texture(game->textures.east);
}

void    free_data(t_data *data)
{
    free (data->north);
    free (data->south);
    free (data->east);
    free (data->west);
}