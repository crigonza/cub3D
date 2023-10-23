/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:29:04 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/23 22:22:42 by crigonza         ###   ########.fr       */
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
    t_data  *data;
    char    *line;
    int     lines;
    int     fd;

    data = (t_data *)malloc(sizeof(t_data));
    data_init(data);
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
    game->data = data;
}

void	set_background(mlx_image_t *img)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_H)
	{
		y = 0;
		while (y < WIN_W)
		{
			mlx_put_pixel(img, y, x, 0x1f2124FF);
			y++;
		}
		x++;
	}
}

int     screen_init(t_game *game)
{
    game->screen->mlx = mlx_init(WIN_W, WIN_H, "cub3D", true);
    game->screen->img = mlx_new_image(game->screen->mlx, WIN_W, WIN_H);
    mlx_image_to_window(game->screen->mlx, game->screen->img, 0, 0);
    mlx_loop(game->screen->mlx);
    //set_background(game);
    return(1);
}

int main(int argc, char **argv)
{
    t_game      *game;
    mlx_t       *mlx;
    mlx_image_t *img;

    if (!check_args(argc, argv))
        exit(EXIT_FAILURE);
    game = (t_game *)malloc(sizeof(t_game));
    mlx = mlx_init(WIN_W, WIN_H, "cub3D", true);
    img = mlx_new_image(mlx, WIN_W, WIN_H);
    mlx_image_to_window(mlx, img, 0, 0);
    set_background(img);
    mlx_loop(mlx);
    //screen_init(game);
    parse_and_check(game, argv[1]);
    //mlx_loop_hook(game->mlx, refresh, &game);
    //mlx_loop(game->screen->mlx);
    //mlx_delete_image(game->screen->mlx, game->screen->img);
    mlx_terminate(mlx);
    game_over(game);
    //free (game);
    system("leaks --q cub3d");
    return (0);
}