/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:23:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/19 19:09:32 by crigonza         ###   ########.fr       */
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

#define BUFFER_SIZE 5

typedef struct s_data
{
    char        *north;
    char        *south;
    char        *west;
    char        *east;
    uint32_t    floor;
    uint32_t    ceiling;
    char        **map; 
}           t_data;


//gnl.c//
/* int         checknl(char *s);
char        *get_line(char *st);
char        *get_st(char *st); */
char        *get_next_line(int fd);
//parser.c//
void        parse_textures(t_data *data, int fd);
void        parser(t_data *data, char *file);



#endif