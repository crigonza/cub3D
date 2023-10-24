/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/24 21:11:04 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/cub3d.h"

void    set_dir(t_player player, char dir)
{
    if (dir == 'N')
    {
        player.dir_x = 0;
        player.dir_y = -1;
    }
    else if (dir == 'S')
    {
        player.dir_x = 0;
        player.dir_y = 1;
    }
    else if (dir == 'W')
    {
        player.dir_x = -1;
        player.dir_y = 0;
    }
    else if (dir == 'E')
    {
        player.dir_x = 1;
        player.dir_y = 0;
    }

}

int     check_player(t_game *game)
{
    int   i;
    int   j;

    i = 0;
    while (i < game->map.map_h) 
    {
        j = 0;
        while (game->map.map_array[i][j])
        {
            if (game->map.map_array[i][j] == 'N' || game->map.map_array[i][j] == 'S' || \
                game->map.map_array[i][j] == 'W' || game->map.map_array[i][j] == 'E')
            {
                game->player.x = (j * TILE_SIZE) + (TILE_SIZE / 2);
                game->player.y = (i * TILE_SIZE) + (TILE_SIZE / 2);
                set_dir(game->player, game->map.map_array[i][j]);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}
int     check_colors(t_data *data)
{
    if (data->floor.red > 255 || data->floor.green > 255 || data->floor.blue > 255 || \
        data->ceiling.red > 255 || data->ceiling.green > 255 || data->ceiling.blue > 255)
    {
        ft_putendl_fd("Error: invalid floor or ceiling rgb color.", 2);
        return (0);
    }
    if (data->floor.red == -1 || data->ceiling.red == -1)
    {
        ft_putendl_fd("Error: missing floor or ceiling color.", 2);
        return (0);
    }
    return (1);
}

int     load_textures(t_data *data, t_game *game)
{
    t_texture   textures;
    int         fd[4];
    
    fd[0] = open(data->north, O_RDONLY);
    fd[1] = open(data->south, O_RDONLY);
    fd[2] = open(data->west, O_RDONLY);
    fd[3] = open(data->east, O_RDONLY);
    if (fd[0] == -1 || fd[1] == -1 || fd[2] == -1 || fd[3] == -1)
    {
        ft_putendl_fd("Error: cant open texture file.", 2);
        return (0);
    }
    close (fd); 
    textures.north = mlx_load_png(data->north);
    textures.south = mlx_load_png(data->south);
    textures.west = mlx_load_png(data->west);
    textures.east = mlx_load_png(data->east);
    game->textures = textures;
    return (1);
}

int     check_data(t_data *data, t_game *game)
{
    if (!data->north || !data->south || !data->west || !data->east)
    {
        ft_putendl_fd("Error: missing wall texture.", 2);
        exit (EXIT_FAILURE);
    }
    if (!load_textures(data, game) || !check_colors(data))
        exit (EXIT_FAILURE);
    if (!game->map.map_array[0])
    {
        ft_putendl_fd("Error: invalid map.", 2);
        exit (EXIT_FAILURE);
    }
    if (!check_player(game))
    {
        ft_putendl_fd("Error: missing player start point.", 2);
        exit (EXIT_FAILURE);
    }
}
