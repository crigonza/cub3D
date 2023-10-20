/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:23:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/20 20:11:02 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../MLX42/include/MLX42/MLX42.h"
#include "../Libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

#define WIN_W 512
#define WIN_H 512

typedef struct s_color
{
    int     red;
    int     green;
    int     blue;
}           t_color;

typedef struct s_player
{
    int      x;
    int      y;
    int      dir_x;
    int      dir_y;
}           t_player;

typedef struct s_data
{
    char        *north;
    char        *south;
    char        *west;
    char        *east;
    t_color     floor;
    t_color     ceiling;
    int         map_start;
    int         map_lines;
    char        **map;
    t_player    player; 
}           t_data;


//checker.c//
void        set_dir(t_player player, char dir);
int         check_player(t_data *data);
int         check_data(t_data *data);
//main.c//
int         check_args(int argc, char **argv);
void        parse_and_check(t_data *data, char *file);
int main(int argc, char **argv);
//parser_utils//
int         spaces_line(char *line);
t_color     get_color(char *rgb);
//parser.c//
void        map_data(t_data *data, int fd, int lines);
void        parse_colors(t_data *data, int fd, int lines);
void        parse_textures(t_data *data, int fd);
void        parse_map(t_data *data, int fd);
//utils.c//
char        *get_next_line(int fd);



#endif