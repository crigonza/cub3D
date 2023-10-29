/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 11:16:15 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/29 12:45:54 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    ray_refresh(t_ray *ray, t_player *player, int x)
{
    ray->camera = 2 * x / (double)WIN_W - 1;
    ray->ray_x = player->dir_x + player->plane_x * ray->camera;
    ray->ray_y = player->dir_y + player->plane_y * ray->camera;
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;
    ray->wall_hit = 0;
    ray->delta_dist_x = fabs(1 / ray->ray_x);
    ray->delta_dist_y = fabs(1 / ray->ray_y);
}

void    ray_dir(t_ray *ray, t_player *player)
{
    if (ray->ray_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
    }
    if (ray->ray_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
    }
}

void    check_hit(t_game *game)
{
    while (game->raycast.wall_hit == 0)
    {
        if (game->raycast.side_dist_x < game->raycast.side_dist_y)
        {
            game->raycast.side_dist_x += game->raycast.delta_dist_x;
            game->raycast.map_x += game->raycast.step_x;
            game->raycast.side_hit = 0;
        }
        else
        {
            game->raycast.side_dist_y += game->raycast.delta_dist_y;
            game->raycast.map_y += game->raycast.step_y;
            game->raycast.side_hit = 1;
        }
        if ((game->raycast.map_x >= 0 && game->raycast.map_x < game->map.map_w &&
            game->raycast.map_y >= 0 && game->raycast.map_y < game->map.map_h &&
            game->map.map_array[game->raycast.map_y][game->raycast.map_x] == '1'))
            game->raycast.wall_hit = 1;
    }
}
void    draw_stripe(t_game *game, int x, int start, int end, int color)
{
    int y;

    y = start;
    while (y <= end)
    {
        mlx_put_pixel(game->img, x, y, color);
        y++;
    }
}

void    get_wall_height(t_game *game, int x)
{
    int line_h;
    int wall_start;
    int wall_end;
    int color;

    color  = 0x4EF4F4;
    line_h = (int)(WIN_H / game->raycast.wall_dist);
    wall_start = -line_h / 2 + WIN_H / 2;
    if (wall_start < 0)
        wall_start = 0;
    wall_end = line_h / 2 + WIN_H / 2;
    if (wall_end >= WIN_H)
        wall_end = -1;
    if (game->raycast.side_hit == 1)
        color = color / 2;
    draw_stripe(game, x, wall_start, wall_end, color);
}

void    raycast(t_game *game)
{
    int x;

    x = 0;
    ray_refresh(&game->raycast, &game->player, x);
    while (x < WIN_W)
    {
        ray_dir(&game->raycast, &game->player);
        check_hit(game);
        if (game->raycast.side_hit == 0)
            game->raycast.wall_dist = (game->raycast.map_x - game->player.pos_x + \
                (1 + game->raycast.step_x) / 2) / game->raycast.ray_x;
        else
            game->raycast.wall_dist = (game->raycast.map_y - game->player.pos_y + \
                (1 + game->raycast.step_y) / 2) / game->raycast.ray_y;
        get_wall_height(game, x);
        x++;
    }
}
