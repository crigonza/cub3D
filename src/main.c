/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:29:04 by crigonza          #+#    #+#             */
/*   Updated: 2023/11/07 09:42:40 by crigonza         ###   ########.fr       */
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

void    parse_and_check(t_game *game, char *file)
{
    t_data  data;
    char    *line;
    int     lines;
    int     fd;

    data_init(&data);
    fd = open(file, O_RDONLY);
    parse_textures(&data, fd);
    close (fd);
    lines = data.map_start;
    fd = open(file, O_RDONLY);
    while (lines > 0)
    {
        line = get_next_line(fd);
        free (line);
        lines--;
    }
    parse_map(&data, fd, game);
    close (fd);
    if(!check_data(&data, game))
    {
        free_data(&data);
        exit (EXIT_FAILURE);
    }
    free_data(&data);
}

int main(int argc, char **argv)
{
    t_game      game;

    if (!check_args(argc, argv))
        exit(EXIT_FAILURE);
    parse_and_check(&game, argv[1]);
    game.mlx = mlx_init(WIN_W, WIN_H, "cub3D", true);
    game.img = mlx_new_image(game.mlx, WIN_W, WIN_H);
    mlx_image_to_window(game.mlx, game.img, 0, 0);
    mlx_set_mouse_pos(game.mlx, WIN_H / 2, WIN_W / 2);
    mlx_loop_hook(game.mlx, main_hook, &game);
    mlx_key_hook(game.mlx, key_hook, &game);
    mlx_mouse_hook(game.mlx, my_mouse_hook, &game);
    mlx_loop(game.mlx);
    game_over(&game);
    mlx_delete_image(game.mlx, game.img);
    mlx_terminate(game.mlx);
    system("leaks --q cub3d");
    return (0);
}
