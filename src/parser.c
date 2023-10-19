/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:33:16 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/19 21:38:46 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_color    get_color(char *rgb)
{
    char        **rgb_split;
    t_color     color;
    int         i;
    
    i = 0;
    rgb_split = ft_split(rgb, ',');
    color.red = ft_atoi(rgb_split[0]);
    color.blue = ft_atoi(rgb_split[1]);
    color.green = ft_atoi(rgb_split[2]);
    if (rgb_split != NULL)
    {
        while (rgb_split[i])
        {
            free(rgb_split[i]);
            i++;
        }
        free (rgb_split);
    }
    return (color);
}

int     spaces_line(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' || line[i] != '\n')
            return (0);
        i++;
    }
    printf("ok");
    return (1);
}

void    map_data(t_data *data, int fd, int lines)
{
    char    *line;
    int     map_len;

    line = NULL;
    map_len = 0;
    while (line = get_next_line(fd))
    {
        if (spaces_line(line))
            lines++;
        else
            map_len++;
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

    line = NULL;
    lines = 0;
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

void    parser(t_data *data, char *file)
{
    int     fd;

    fd = open(file, O_RDONLY);
    parse_textures(data, fd);
    close (fd);
    printf("%d\n", data->map_lines);
    printf("%d\n", data->map_start);
}