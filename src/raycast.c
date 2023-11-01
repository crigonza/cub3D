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
    /* if (ray->ray_x != 0)
        ray->delta_dist_x = fabs(1 / ray->ray_x);
    if (ray->ray_y != 0)
        ray->delta_dist_y = fabs(1 / ray->ray_y); */
    ray->delta_dist_x = sqrt(1 + (ray->ray_y * ray->ray_y) / (ray->ray_x * ray->ray_x));
    ray->delta_dist_y = sqrt(1 + (ray->ray_x * ray->ray_x) / (ray->ray_y * ray->ray_y));
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
        if (game->raycast.map_x < WIN_W && game->raycast.map_y < WIN_H)
        {
            if (game->map.map_array[game->raycast.map_y][game->raycast.map_x] == '1')
                game->raycast.wall_hit = 1;
        }
    }
}

void draw_sky_and_floor(t_game *game, int x)
{
    int y;

    y = 0;
    while (y < WIN_H / 2)
    {
        mlx_put_pixel(game->img, x, y, 0x1B4965);
        y++;
    }
    while (y < WIN_H)
    {
        mlx_put_pixel(game->img, x, y, 0x5FA8D3);
        y++;
    }
}

int     get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
    int         rgba;
    t_color     color;
    uint8_t     *pixel;
    
    if (y > texture->height)
        y = y % texture->height;
    pixel = texture->pixels + (y *texture->width + x) * texture->bytes_per_pixel;
    color.red = pixel[0];
    color.green = pixel[0];
    color.blue = pixel[0];
    color.alpha = pixel[0];
    rgba = get_rgba(color.red, color.green, color.blue, color.alpha);
}

void    draw_stripe(t_game *game, int x, int start, int end, int color)
{
    int y;

    y = start;
    while (y <= end)
    {
        color = get_texture_pixel(game->textures.north, x, y);
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
        wall_end = WIN_H - 1;
    if (game->raycast.side_hit == 1)
        color = color / 2;
    draw_stripe(game, x, wall_start, wall_end, color);
}

void    raycast(t_game *game)
{
    int x;

    x = 0;
    while (x < WIN_W)
    {
        game->raycast.wall_hit = 0;
        game->raycast.map_x = (int)game->player.pos_x;
        game->raycast.map_y = (int)game->player.pos_y;
        ray_refresh(&game->raycast, &game->player, x);
        ray_dir(&game->raycast, &game->player);
        check_hit(game);
        if (game->raycast.side_hit == 0)
            game->raycast.wall_dist = ((game->raycast.map_x - game->player.pos_x + \
                (1 - game->raycast.step_x) / 2) / game->raycast.ray_x);
        else
            game->raycast.wall_dist = ((game->raycast.map_y - game->player.pos_y + \
                (1 - game->raycast.step_y) / 2) / game->raycast.ray_y);
        draw_sky_and_floor(game, x);
        get_wall_height(game, x);
        x++;
    }
}
