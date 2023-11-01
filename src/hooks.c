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
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
        rotate_left(&game->player);
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
        rotate_right(&game->player);
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
        move_forward(game);
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
        move_backward(game);
}

void    main_hook(void *params)
{
    t_game  *game;

    game = (t_game*)params;
    raycast(game);
}