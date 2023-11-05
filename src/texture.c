/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:49:52 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/05 18:53:08 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void    get_wall_texture(t_game * game)
{
    if (game->raycast.side_hit == 0)
    {
        if (game->raycast.ray_x > 0)
            game->wall_tex.tex = game->textures.west;
        else
            game->wall_tex.tex = game->textures.east;
    }
    else
    {
        if (game->raycast.ray_y > 0)
            game->wall_tex.tex = game->textures.north;
        else
            game->wall_tex.tex = game->textures.south;
    }
}

void    set_tex_params(t_wall_tex *wall_tex, t_ray *ray)
{
    if (wall_tex->tex->height == wall_tex->tex->width / 2)
        ray->wall_x /= 2;
    else if (wall_tex->tex->height == wall_tex->tex->width / 3)
        ray->wall_x /= 3;
    ray->wall_x -= floor(ray->wall_x);
    if (ray->side_hit == 0)
    {
        if (ray->step_x > 0)
            wall_tex->tex_x = (int)(ray->wall_x * (double)(wall_tex->tex->width));
        else
            wall_tex->tex_x = wall_tex->tex->width - (int)(ray->wall_x * (double)(wall_tex->tex->width)) - 1;
    }
    else
    {
        if (ray->step_y > 0)
            wall_tex->tex_x = wall_tex->tex->width - (int)(ray->wall_x * (double)(wall_tex->tex->width)) - 1;
        else
            wall_tex->tex_x = (int)(ray->wall_x * (double)(wall_tex->tex->width));
    }
}