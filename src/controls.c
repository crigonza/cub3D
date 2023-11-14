/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:59:53 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/14 11:35:46 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_game *game)
{
	double	newposx;
	double	newposy;
	double	collision_margin;

	collision_margin = 0.2;
	newposx = game->player.pos_x + game->player.dir_x * game->player.speed;
	newposy = game->player.pos_y + game->player.dir_y * game->player.speed;
	if (game->map.map_array[(int)game->player.pos_y][(int)(newposx
		+ game->player.dir_x * collision_margin)] != '1')
		game->player.pos_x = newposx;
	if (game->map.map_array[(int)(newposy + game->player.dir_y
			* collision_margin)][(int)game->player.pos_x] != '1')
		game->player.pos_y = newposy;
}

void	move_backward(t_game *game)
{
	double	newposx;
	double	newposy;
	double	collision_margin;

	collision_margin = 0.2;
	newposx = game->player.pos_x - game->player.dir_x * game->player.speed;
	newposy = game->player.pos_y - game->player.dir_y * game->player.speed;
	if (game->map.map_array[(int)game->player.pos_y][(int)(newposx
		- game->player.dir_x * collision_margin)] != '1')
		game->player.pos_x = newposx;
	if (game->map.map_array[(int)(newposy - game->player.dir_y
			* collision_margin)][(int)game->player.pos_x] != '1')
		game->player.pos_y = newposy;
}

void	move_right(t_game *game)
{
	double	newposx;
	double	newposy;
	double	collision_margin;

	collision_margin = 0.2;
	newposx = game->player.pos_x - game->player.dir_y * game->player.speed;
	newposy = game->player.pos_y + game->player.dir_x * game->player.speed;
	if (game->map.map_array[(int)game->player.pos_y][(int)(newposx
		- game->player.dir_y * collision_margin)] != '1')
		game->player.pos_x = newposx;
	if (game->map.map_array[(int)(newposy + game->player.dir_x
			* collision_margin)][(int)game->player.pos_x] != '1')
		game->player.pos_y = newposy;
}

void	move_left(t_game *game)
{
	double	newposx;
	double	newposy;
	double	collision_margin;

	collision_margin = 0.2;
	newposx = game->player.pos_x + game->player.dir_y * game->player.speed;
	newposy = game->player.pos_y - game->player.dir_x * game->player.speed;
	if (game->map.map_array[(int)game->player.pos_y][(int)(newposx
		+ game->player.dir_y * collision_margin)] != '1')
		game->player.pos_x = newposx;
	if (game->map.map_array[(int)(newposy - game->player.dir_x
			* collision_margin)][(int)game->player.pos_x] != '1')
		game->player.pos_y = newposy;
}

void	rotate(t_player *player, float angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y
		* sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}
