/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:46:12 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/05 19:09:58 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    draw_sky_and_floor(t_game *game, int x)
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

int     dim_color(t_color *color, double dist)
{
    int     new_color;

    //printf("distancia: %f\n", dist);
    dist /= 1.5;
    if (dist < 1)
        dist = 1;
    /* else if (dist > 3)
        dist = 3; */
    color->red /= dist;
    color->green /= dist;
    color->blue /= dist;
    new_color = get_rgba(color->red, color->green, color->blue, color->alpha);
    return (new_color);
}

void    draw_stripe(t_game *game, int x, int start, int end)
{
    int             y;
    int             dimmed_color;
    t_color         color;

    y = start;
    get_wall_texture(game);
    set_tex_params(&game->wall_tex, &game->raycast);
    while (y <= end)
    {
        game->wall_tex.tex_y = ((int)game->wall_tex.tex_pos) % game->wall_tex.tex->height;
        game->wall_tex.tex_pos += game->wall_tex.tex_step;
        color = get_texture_pixel(game->wall_tex.tex, game->wall_tex.tex_x, game->wall_tex.tex_y);
        dimmed_color = dim_color(&color, game->raycast.wall_dist);
        mlx_put_pixel(game->img, x, y, dimmed_color);
        y++;
    }
}