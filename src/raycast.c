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
    ray->hit = 0;
    ray->map_x = (int)player->pos_x;
    ray->map_y = (int)player->pos_y;
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
    while (game->raycast.hit == 0)
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
                game->raycast.hit = 1;
        }
    }
}

void draw_sky_and_floor(t_game *game, int x)
{
    int y;

    y = 0;
    while (y < WIN_H / 2)
    {
        mlx_put_pixel(game->img, x, y, game->textures.ceiling_color);
        y++;
    }
    while (y < WIN_H)
    {
        mlx_put_pixel(game->img, x, y, game->textures.floor_color);
        y++;
    }
}

t_color     get_texture_pixel(mlx_texture_t *texture, int x, int y)
{
    //int         rgba;
    t_color     color;
    uint8_t     *pixel;
    
    /* if (y > texture->height)
        y = y % texture->height;
    if (x > texture->width)
        x = x % texture->width; */
    pixel = texture->pixels + (y *texture->width + x) * texture->bytes_per_pixel;
    color.red = pixel[0];
    color.green = pixel[1];
    color.blue = pixel[2];
    color.alpha = pixel[3];
    // rgba = get_rgba(color.red, color.green, color.blue, color.alpha);
    return (color);
}

void    set_tex_params(t_texture *texture, mlx_texture_t *tex, t_ray *ray)
{
    if (ray->side_hit == 0 && ray->ray_x > 0)
        texture->tex_x = tex->width - (int)(ray->wall_x * (double)(tex->width)) - 1;
    else if (ray->side_hit == 0 && ray->ray_y < 0)
        texture->tex_x = tex->width - (int)(ray->wall_x * (double)(tex->width)) - 1;
    else
        texture->tex_x = (int)(ray->wall_x * (double)(tex->width));
    // printf("tex x: %d", texture->tex_x);
    
}

int     dim_color(t_color *color, double dist)
{
    int     new_color;

    //printf("distancia: %f\n", dist);
    dist /= 1.5;
    if (dist < 1)
        dist = 1;
    else if (dist > 3)
        dist = 3;
    color->red /= dist;
    color->green /= dist;
    color->blue /= dist;
    new_color = get_rgba(color->red, color->green, color->blue, color->alpha);
    return (new_color);
}

void    draw_stripe(t_game *game, int x, int start, int end)
{
    int         y;
    int         dimmed_color;
    t_color     color;

    y = start;
    set_tex_params(&game->textures, game->textures.north, &game->raycast);
    while (y <= end)
    {
        game->textures.tex_y = ((int)game->textures.tex_pos) % game->textures.north->height;
        game->textures.tex_pos += game->textures.tex_step;
        // printf("tex_pos : %f", game->textures.tex_pos);
        // printf("tex x: %d || ", game->textures.tex_x);
        // printf("tex y: %d\n", game->textures.tex_y);
        color = get_texture_pixel(game->textures.north, game->textures.tex_x, game->textures.tex_y);
        dimmed_color = dim_color(&color, game->raycast.wall_dist);
        mlx_put_pixel(game->img, x, y, dimmed_color);
        y++;
    }
}

void    get_wall_height(t_game *game, int x)
{
    int line_h;
    int wall_start;
    int wall_end;

    line_h = (int)(WIN_H / game->raycast.wall_dist);
    wall_start = -line_h / 2 + WIN_H / 2;
    if (wall_start < 0)
        wall_start = 0;
    wall_end = line_h / 2 + WIN_H / 2;
    if (wall_end >= WIN_H)
        wall_end = WIN_H - 1;
    /* if (game->raycast.side_hit == 1)
        color = color / 2; */
    game->textures.tex_step = 1.0 * game->textures.north->height / line_h;
    game->textures.tex_pos = (wall_start - WIN_H / 2 + line_h / 2) * game->textures.tex_step;
    //printf("tex_step : %f || ", game->textures.tex_step);
    draw_stripe(game, x, wall_start, wall_end);
}

void    raycast(t_game *game)
{
    int x;

    x = 0;
    while (x < WIN_W)
    {
        ray_refresh(&game->raycast, &game->player, x);
        ray_dir(&game->raycast, &game->player);
        check_hit(game);
        if (game->raycast.side_hit == 0)
        {
            game->raycast.wall_dist = ((game->raycast.map_x - game->player.pos_x + \
                (1 - game->raycast.step_x) / 2) / game->raycast.ray_x);
            game->raycast.wall_x = game->player.pos_y + game->raycast.wall_dist * game->raycast.ray_y;
        }
        else
        {
            game->raycast.wall_dist = ((game->raycast.map_y - game->player.pos_y + \
                (1 - game->raycast.step_y) / 2) / game->raycast.ray_y);
            game->raycast.wall_x = game->player.pos_x + game->raycast.wall_dist * game->raycast.ray_x;
        }
        game->raycast.wall_x -= floor(game->raycast.wall_x);
        // printf("wall_x : %f ||| ", game->raycast.wall_x);
        draw_sky_and_floor(game, x);
        get_wall_height(game, x);
        x++;
    }
}
