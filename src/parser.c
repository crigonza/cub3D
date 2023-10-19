/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:33:16 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/19 19:28:10 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

uint32_t    transform_color(char *rgb)
{
    char        *rgb_split;
    uint32_t    rgb_int;

    rgb_split = ft_split(rgb, ',');
    rgb_int = ((rgb_split[0] << 16) | (rgb_split[1] << 8) | rgb_split[2]);
    /* while(rgb_split)
    {
        free (*rgb_split);
        *rgb_split++;
    }
    free (rgb); */
    return (rgb_int);
}

void    parse_colors(t_data *data, int fd)
{
    char    *line;

    line = NULL;
    data->floor = -1;
    data->ceiling = -1;
    while (line = get_next_line(fd))
    {
        if (!ft_strncmp(line, "F ", 2))
            data->floor = transform_color(ft_substr(line, 2, ft_strlen(line)));
        free(line);
        if (data->floor != -1)
            break;
    }
    printf("%d", data->floor);
}

void    parse_textures(t_data *data, int fd)
{
    char    *line;

    line = NULL;
    while (line = get_next_line(fd))
    {
        if (!ft_strncmp(line, "NO ", 3))
            data->north = ft_substr(line, 3, ft_strlen(line));
        if (!ft_strncmp(line, "SO ", 3))
            data->south = ft_substr(line, 3, ft_strlen(line));
        if (!ft_strncmp(line, "WE ", 3))
            data->west = ft_substr(line, 3, ft_strlen(line));
        if (!ft_strncmp(line, "EA ", 3))
            data->east = ft_substr(line, 3, ft_strlen(line));
        free (line);
        if (data->north && data->south && data->west && data->east)
            break;
    }
    parse_colors(data, fd);
}

void    parser(t_data *data, char *file)
{
    int     fd;

    fd = open(file, O_RDONLY);
    parse_textures(data, fd);
    close (fd);
}