/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 17:07:42 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/29 11:47:30 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    data_init(t_data *data)
{
    data->north = NULL;
    data->south = NULL;
    data->west = NULL;
    data->east = NULL;
    data->floor.red = -1;
    data->floor.green = -1;
    data->floor.blue = -1;
    data->ceiling.red = -1;
    data->ceiling.green = -1;
    data->ceiling.blue = -1;
    data->map_start = 0;
    data->map_lines = 0;
}
