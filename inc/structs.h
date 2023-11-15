/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:54:04 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/15 17:09:03 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_color
{
	int				red;
	int				green;
	int				blue;
	int				alpha;
}					t_color;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			speed;
	double			rotate_speed;
}					t_player;

typedef struct s_texture
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	int				floor_color;
	int				ceiling_color;
}					t_texture;

typedef struct s_wall_tex
{
	mlx_texture_t	*tex;
	int				tex_x;
	int				tex_y;
	double			tex_step;
	double			tex_pos;
}					t_wall_tex;

typedef struct s_ray
{
	double			camera;
	double			ray_x;
	double			ray_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			wall_dist;
	double			wall_x;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side_hit;
}					t_ray;

typedef struct s_data
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	t_color			floor;
	t_color			ceiling;
	int				map_start;
	int				map_lines;
}					t_data;

typedef struct s_map
{
	char			**map_array;
	int				map_h;
	int				map_w;
}					t_map;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*spt;
	t_map			map;
	t_player		player;
	t_texture		textures;
	t_wall_tex		wall_tex;
	t_ray			raycast;
}					t_game;

#endif
