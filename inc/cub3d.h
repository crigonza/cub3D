/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:23:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/29 12:49:00 by crigonza         ###   ########.fr       */
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

#define WIN_W 800
#define WIN_H 600
#define MAX_DISTANCE 1000
#define SCALE_FACTOR 1.5;

typedef struct s_point
{
    int     x;
    int     y;
}           t_point;

typedef struct s_color
{
    int     red;
    int     green;
    int     blue;
}           t_color;

typedef struct s_player
{
    double      pos_x;
    double      pos_y;
    double      dir_x;
    double      dir_y;
    double      plane_x;
    double      plane_y;
    double      speed;
    double      rotate_speed;
}           t_player;

typedef struct s_texture
{
    mlx_texture_t   *north;
    mlx_texture_t   *south;
    mlx_texture_t   *west;
    mlx_texture_t   *east;
    int             floor_color;
    int             ceiling_color;
}           t_texture;

typedef struct s_ray
{
    double      camera;
    double      ray_x;
    double      ray_y;
    double      side_dist_x;
    double      side_dist_y;
    double      delta_dist_x;
    double      delta_dist_y;
    double      wall_dist;
    int         map_x;
    int         map_y;
    int         step_x;
    int         step_y;
    int         wall_hit;
    int         side_hit;
}           t_ray;

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
}           t_data;

typedef struct s_map
{
    char        **map_array;
    int         map_h;
    int         map_w;
}           t_map;

typedef struct s_game
{
    mlx_t       *mlx;
    mlx_image_t *img;
    t_map       map;
    t_player    player;
    t_texture   textures;
    t_ray       raycast;
}           t_game;

//check_map//
int         check_first_and_last(char *first, char *last);
int         check_map_point(char **map, int y, int x);
int         check_map(t_map map);
//checker.c//
void        set_dir(t_player player, char dir);
int         check_player(t_game *game);
int         check_colors(t_data *data);
int         load_textures(t_data *data, t_game *game);
int         check_data(t_data *data, t_game *game);
//controls.c//
void        move_forward(t_game *game);
void        move_backward(t_game *game);
void        rotate_left(t_player *player);
void        rotate_right(t_player *player);
//free_utils//
void        game_over(t_game *game);
void        free_data(t_data *data);
//hooks.c//
void        key_hook(mlx_key_data_t keydata, t_game *game);
//initialize.c//
void        data_init(t_data *data);
//main.c//
int         check_args(int argc, char **argv);
void        parse_and_check(t_game *game, char *file);
int         main(int argc, char **argv);
//parser_utils//
int         spaces_line(char *line);
char        *get_path(char *line);
t_color     get_color(char *rgb);
//parser.c//
void        map_data(t_data *data, int fd, int lines);
void        parse_colors(t_data *data, int fd, int lines);
void        parse_textures(t_data *data, int fd);
void        parse_map(t_data *data, int fd, t_game *game);
//raycast.c//
void        raycast(t_game *game);
//utils.c//
char        *get_next_line(int fd);
int         get_rgba(int r, int g, int b, int a);



#endif