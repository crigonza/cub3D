/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:02:56 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/15 19:37:06 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d_bonus.h"

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
		angle = (0.01 * (pos_x - WIN_W / 2) * game->player.rotate_speed);
		rotate(&game->player, angle);
	}
	if (pos_x > WIN_H - (WIN_H / 3))
		mlx_set_mouse_pos(game->mlx, WIN_H - (WIN_H / 3), WIN_W / 2);
	if (pos_x < WIN_H / 3)
		mlx_set_mouse_pos(game->mlx, WIN_H / 3, WIN_W / 2);
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
