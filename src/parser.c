/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:33:16 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/20 18:56:35 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    map_data(t_data *data, int fd, int lines)
{
    char    *line;
    int     map_len;

    line = NULL;
    map_len = 0;
    while (line = get_next_line(fd))
    {
        if (!spaces_line(line))
            map_len++;
        else
            lines++;
        free (line);
    }
    data->map_lines = map_len;
    data->map_start = lines;
}

void    parse_colors(t_data *data, int fd, int lines)
{
    char    *line;

    line = NULL;
    data->floor.red = -1;
    data->ceiling.red = -1;
    while (line = get_next_line(fd))
    {
        if (!ft_strncmp(line, "F ", 2))
            data->floor = get_color(ft_substr(line, 2, ft_strlen(line)));
        if (!ft_strncmp(line, "C ", 2))
            data->ceiling = get_color(ft_substr(line, 2, ft_strlen(line)));
        free(line);
        lines++;
        if (data->ceiling.red != -1)
            break;
    }
    map_data(data, fd, lines);
}

void    parse_textures(t_data *data, int fd)
{
    char    *line;
    int     lines;

    lines = 0;
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
        lines++;
        if (data->north && data->south && data->west && data->east)
            break;
    }
    parse_colors(data, fd, lines);
}

void    parse_map(t_data *data, int fd)
{
    int     i;
    char    *line;

    i = 0;
    line = NULL;
    data->map = (char *)malloc(sizeof(char) * data->map_lines);
    while (i < data->map_lines)
    {
        line = get_next_line(fd);
        data->map[i] = ft_strdup(line);
        free (line);
        i++;
    }
    i = 0;
    /* while (i < data->map_lines)
    {
        printf("%s", data->map[i]);
        i++;
    } */
}
