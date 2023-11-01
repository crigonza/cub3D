/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:54:17 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/24 19:34:46 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int     spaces_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

char    *get_path(char *line)
{
    char    *path;
    int     i;
    int     j;

    i = 3;
    j = 0;
    path = (char *)malloc(sizeof(char) * (ft_strlen(line) - 3));
    while(line[i] != '\n')
    {
        path[j] = line[i];
        j++;
        i++;
    }
    path[j] = '\0';
    return (path);
}

t_color    get_color(char *rgb)
{
    char        **rgb_split;
    t_color     color;
    int         i;
    
    i = 0;
    rgb_split = ft_split(rgb, ',');
    color.red = ft_atoi(rgb_split[0]);
    color.green = ft_atoi(rgb_split[1]);
    color.blue = ft_atoi(rgb_split[2]);
    if (rgb_split != NULL)
    {
        while (rgb_split[i])
        {
            free(rgb_split[i]);
            i++;
        }
        free (rgb_split);
    }
    free (rgb);
    return (color);
}
