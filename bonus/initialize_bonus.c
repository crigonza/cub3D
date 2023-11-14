/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:07:42 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/14 13:52:29 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	data_init(t_data *data)
{
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	data->floor.red = -1;
	data->floor.green = -1;
	data->floor.blue = -1;
	data->ceiling.red = -1;
	data->ceiling.green = -1;
	data->ceiling.blue = -1;
	data->map_start = 0;
	data->map_lines = 0;
}

void	sprite_init(t_game *game)
{
	game->spt = mlx_new_image(game->mlx, WIN_W, WIN_H);
	mlx_image_to_window(game->mlx, game->spt, WIN_W - 512, WIN_H - 512);
	game->sprite.frame_num = 0;
	game->sprite.frame_counter = 0;
	game->sprite.frame1 = mlx_load_png("./textures/hand1.png");
	game->sprite.frame2 = mlx_load_png("./textures/hand2.png");
	game->sprite.frame3 = mlx_load_png("./textures/hand3.png");
	game->sprite.frame4 = mlx_load_png("./textures/hand4.png");
}
