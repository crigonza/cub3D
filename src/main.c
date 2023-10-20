/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:29:04 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/20 20:24:41 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int check_args(int argc, char **argv)
{
    char    *tmp;
    int fd;

    if (argc != 2)
    {
        ft_putendl_fd("Error: invalid arguments number.", 2);
        return (0);
    }
    tmp = ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]));
    if (tmp == NULL)
    {
        ft_putendl_fd("Error: invalid map archive.", 2);
        return (0);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        ft_putendl_fd("Error: invalid archive format.", 2);
        close (fd);
        return (0);
    }
    close (fd);
    return (1);
}

void    parse_and_check(t_data *data, char *file)
{
    char    *line;
    int     lines;
    int     fd;

    fd = open(file, O_RDONLY);
    parse_textures(data, fd);
    close (fd);
    lines = data->map_start;
    fd = open(file, O_RDONLY);
    while (lines > 0)
    {
        line = get_next_line(fd);
        free (line);
        lines--;
    }
    parse_map(data, fd);
    close (fd);
    check_data(data);
}

int main(int argc, char **argv)
{
    t_data  *data;
    // mlx_t   *mlx;
    // mlx_image_t *img;

    data = (t_data *)malloc(sizeof(t_data));
    if (!check_args(argc, argv))
        exit(EXIT_FAILURE);
    parse_and_check(data, argv[1]);

    /* mlx = mlx_init(WIN_W, WIN_H, "Cub3D", true);
    img = mlx_new_image(mlx, WIN_W, WIN_H);
    mlx_image_to_window(mlx, img, 0, 0);
    mlx_put_pixel(img, data->player.x, data->player.y, 322113); */
    
    system("leaks --q cub3d");
    return (0);
}