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

void    refresh(void *param)
{
    t_game      *game;

    game = (t_game *)param;
    /* if (game->img)
        mlx_delete_image(game->mlx, game->img); */
    game->img = mlx_new_image(game->mlx, WIN_W, WIN_H);
    mlx_image_to_window(game->mlx, game->img, 0, 0);
    raycast(game);
    //mlx_loop(game->mlx);
}