/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 18:02:56 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/29 12:54:44 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    key_hook(mlx_key_data_t keydata, void *params)
{
    t_game  *game;

    game = params;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window(game->mlx);
    if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        move_left(game);
    if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        move_right(game);
    if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        move_forward(game);
    if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        move_backward(game);
    if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        rotate_left(&game->player);
    if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT))
        rotate_right(&game->player);
}

void    my_mouse_hook(double pos_x, double pos_y, void *params)
{
    t_game  *game;

    game = params;
    (void)pos_y;
    if (pos_x > WIN_W / 2 + 25)
    {
		game->player.rotate_speed = .05;
        rotate_right(&game->player);
    }
	else if (pos_x < WIN_W / 2 - 25)
	{
        game->player.rotate_speed = .05;
        rotate_left(&game->player);
    }
	if (pos_x > WIN_W / 2 + 25 || pos_x < WIN_W / 2 - 25
		|| pos_y > WIN_H / 2 + 25 || pos_y < WIN_H - 25)
		mlx_set_mouse_pos(game->mlx, WIN_W / 2, WIN_H / 2);
}

void    main_hook(void *params)
{
    t_game  *game;

    game = (t_game*)params;
    raycast(game);
}
