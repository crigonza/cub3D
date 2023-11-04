/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 17:33:16 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/27 20:58:18 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    map_data(t_data *data, int fd, int lines)
{
    char    *line;
    int     map_len;

    line = NULL;
    map_len = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (!spaces_line(line))
            map_len++;
        else
            lines++;
        free (line);
        line = get_next_line(fd);
    }
    free (line);
    data->map_lines = map_len;
    data->map_start = lines;
    /* printf("map start = %d\n", data->map_start);
    printf("map lines = %d\n", data->map_lines); */
}

void    parse_colors(t_data *data, int fd, int lines)
{
    char    *line;

    line = NULL;
    line = get_next_line(fd);
    while (line)
    {
        if (!ft_strncmp(line, "F ", 2))
            data->floor = get_color(ft_substr(line, 2, ft_strlen(line)));
        if (!ft_strncmp(line, "C ", 2))
            data->ceiling = get_color(ft_substr(line, 2, ft_strlen(line)));
        free(line);
        lines++;
        if (data->ceiling.red != -1)
            break;
        line = get_next_line(fd);
    }
    // printf("lineas despues de los colores: %d\n", lines);
    map_data(data, fd, lines);
}

void    parse_textures(t_data *data, int fd)
{
    char    *line;
    int     lines;

    lines = 0;
    line = NULL;
    line = get_next_line(fd);
    while (line)
    {
        if (!ft_strncmp(line, "NO ", 3))
            data->north = get_path(line);
        if (!ft_strncmp(line, "SO ", 3))
            data->south = get_path(line);
        if (!ft_strncmp(line, "WE ", 3))
            data->west = get_path(line);
        if (!ft_strncmp(line, "EA ", 3))
            data->east = get_path(line);
        free (line);
        lines++;
        if (data->north && data->south && data->west && data->east)
            break;
        line = get_next_line(fd);
    }
    // printf("lineas despues de las texturas: %d\n", lines);
    parse_colors(data, fd, lines);
}

void    parse_map(t_data *data, int fd, t_game *game)
{
    int     i;
    int     len;
    int     width;
    char    *line;

    i = 0;
    width = 0;
    line = NULL;
    game->map.map_h = data->map_lines;
    game->map.map_array = (char **)malloc(sizeof(char *) * data->map_lines);
    while (i < data->map_lines)
    {
        line = get_next_line(fd);
        game->map.map_array[i] = ft_strdup(line);
        len = ft_strlen(line);
        if (width < len)
            width = len;
        free (line);
        i++;
    }
    game->map.map_w = width;
    /* printf ("ANCHO DEL MAPA : %d\n", game->map.map_w);
    printf ("ALTO DEL MAPA : %d\n", game->map.map_h);
    i = 0;
    while (i < data->map_lines)
    {
        printf("%s", game->map.map_array[i]);
        i++;
    } */
}
