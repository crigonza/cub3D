/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:08:18 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/07 09:37:25 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


int     check_map_chars(t_map map)
{
    int x;
    int y;

    y = 0;
    while (y < map.map_h)
    {
        x = 0;
        while (x < map.map_w)
        {
        if ((ft_strchr("10WESN", map.map_array[y][x]) == NULL))
            {
                if (map.map_array[y][x] != 32 && map.map_array[y][x] != 10  && \
                    map.map_array[y][x] != '\t' && map.map_array[y][x] != '\0' && \
                    map.map_array[y][x] != 1) 
                    {
                        return(0);
                    }
            }
            x++;
        }
        y++;
    }
    return(1);
}

int     check_first_and_last(char *first, char *last)
{
    int x;

    x = 0;
    while (first[x] && first[x] != '\n')
    {
        if (first[x] != '1' && first[x] != 32)
            return (0);
        x++;
    }
    x = 0;
    while (last[x] && last[x] != '\n')
    {
        if (last[x] != '1' && last[x] != 32)
            return (0);
        x++;
    }
    return (1);
}

int     check_map_point(char **map, int y, int x)
{
    if (x == 0)
        return (0);
    else if (map[y][x - 1] == 32 || map[y][x + 1] == 32)
        return (0);
    else if (map[y][x - 1] == 10 || map[y][x + 1] == 10)
        return (0);
    else if (map[y - 1][x] == 32 || map[y + 1][x] == 32)
        return (0);
    return (1);
}

int     check_map(t_map map)
{
    int x;
    int y;

    if (!check_map_chars(map))
        return(0);
    y = 1;
    if (!check_first_and_last(map.map_array[0], map.map_array[map.map_h - 1]))
        return(0);
    while (y < map.map_h - 1)
    {
        x = 0;
        while (x < map.map_w)
        {
            if (map.map_array[y][x] == '0')
            {
                if (!check_map_point(map.map_array, y, x))
                    return (0);
            }
            x++;
        }
        y++;
    }
    return (1);
}