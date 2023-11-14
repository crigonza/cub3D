/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itorres- <itorres-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:02:56 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/14 13:14:10 by itorres-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *params)
{
	t_game	*game;

	game = params;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

void	my_mouse_hook(double pos_x, double pos_y, void *params)
{
	t_game	*game;
	double	angle;

	game = params;
	(void)pos_y;
	if (pos_x != WIN_W / 2)
	{
		angle = (.001 * (pos_x - WIN_W / 2) * game->player.rotate_speed);
		rotate(&game->player, angle);
	}
}

void	draw_texture(t_game *game, mlx_texture_t *tex)
{
	t_color	color;
	int		rgba;
	int		y;
	int		x;

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

void	main_hook(void *params)
{
	t_game	*game;

	game = (t_game *)params;
	raycast(game);
	if (game->bonus)
		draw_sprite(game);
	minimap_squares(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_forward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_backward(game);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(&game->player, -game->player.rotate_speed);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(&game->player, game->player.rotate_speed);
}
