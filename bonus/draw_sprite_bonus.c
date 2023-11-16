/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 19:35:48 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/16 09:38:11 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

void	draw_texture(t_game *game, mlx_texture_t *tex)
{
	t_color		color;
	int			rgba;
	uint32_t	y;
	uint32_t	x;

	y = 0;
	while (y < tex->height)
	{
		x = 0;
		while (x < tex->width)
		{
			color = get_texture_pixel(tex, x, y);
			rgba = get_rgba(color.red, color.green, color.blue,
					color.alpha);
			mlx_put_pixel(game->spt, x, y, rgba);
			x++;
		}
		y++;
	}
}

void	draw_sprite(t_game *game)
{
	mlx_texture_t	*tex;

	game->sprite.frame_counter++;
	if (game->sprite.frame_counter == 15)
	{
		if (game->sprite.frame_num == 0)
			tex = game->sprite.frame1;
		if (game->sprite.frame_num == 1)
			tex = game->sprite.frame2;
		if (game->sprite.frame_num == 2)
			tex = game->sprite.frame3;
		if (game->sprite.frame_num == 3)
			tex = game->sprite.frame4;
		game->sprite.frame_counter = 0;
		game->sprite.frame_num++;
		draw_texture(game, tex);
		if (game->sprite.frame_num == 4)
			game->sprite.frame_num = 0;
	}
}
