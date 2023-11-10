/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 17:59:53 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/10 18:12:02 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void move_forward(t_game *game)
{
    double newPosX;
    double newPosY;
    double collision_margin;

    collision_margin = 0.2;
    newPosX = game->player.pos_x + game->player.dir_x * game->player.speed;
    newPosY = game->player.pos_y + game->player.dir_y * game->player.speed;
    if (game->map.map_array[(int)game->player.pos_y][(int)(newPosX + game->player.dir_x * collision_margin)] != '1')
        game->player.pos_x = newPosX;
    if (game->map.map_array[(int)(newPosY + game->player.dir_y * collision_margin)][(int)game->player.pos_x] != '1')
        game->player.pos_y = newPosY;
}

void move_backward(t_game *game)
{
    double newPosX;
    double newPosY;
    double collision_margin;

    collision_margin = 0.2;
    newPosX = game->player.pos_x - game->player.dir_x * game->player.speed;
    newPosY = game->player.pos_y - game->player.dir_y * game->player.speed;
    if (game->map.map_array[(int)game->player.pos_y][(int)(newPosX - game->player.dir_x * collision_margin)] != '1')
        game->player.pos_x = newPosX;
    if (game->map.map_array[(int)(newPosY - game->player.dir_y * collision_margin)][(int)game->player.pos_x] != '1')
        game->player.pos_y = newPosY;
}

void move_right(t_game *game)
{
    double newPosX;
    double newPosY;
    double collision_margin;

    collision_margin = 0.2;
    newPosX = game->player.pos_x - game->player.dir_y * game->player.speed;
    newPosY = game->player.pos_y + game->player.dir_x * game->player.speed;
    if (game->map.map_array[(int)game->player.pos_y][(int)(newPosX - game->player.dir_y * collision_margin)] != '1')
        game->player.pos_x = newPosX;
    if (game->map.map_array[(int)(newPosY + game->player.dir_x * collision_margin)][(int)game->player.pos_x] != '1')
        game->player.pos_y = newPosY;
}

void move_left(t_game *game)
{
    double newPosX;
    double newPosY;
    double collision_margin;

    collision_margin = 0.2;
    newPosX = game->player.pos_x + game->player.dir_y * game->player.speed;
    newPosY = game->player.pos_y - game->player.dir_x * game->player.speed;
    if (game->map.map_array[(int)game->player.pos_y][(int)(newPosX + game->player.dir_y * collision_margin)] != '1')
        game->player.pos_x = newPosX;
    if (game->map.map_array[(int)(newPosY - game->player.dir_x * collision_margin)][(int)game->player.pos_x] != '1')
        game->player.pos_y = newPosY;
}

void rotate(t_player *player, float angle)
{
    double  old_dir_x;
    double  old_plane_x;

    old_dir_x = player->dir_x;
    old_plane_x = player->plane_x;
    player->dir_x = player->dir_x * cos(angle) - player->dir_y * sin(angle);
    player->dir_y = old_dir_x * sin(angle) + player->dir_y * cos (angle);
    player->plane_x  = player->plane_x * cos(angle) - player->plane_y * sin(angle);
    player->plane_y  = old_plane_x * sin(angle) + player->plane_y * cos(angle);
}