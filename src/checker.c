/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:47:24 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/20 19:41:27 by crigonza         ###   ########.fr       */
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

int     check_player(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (i < data->map_lines) 
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' || \
                data->map[i][j] == 'W' || data->map[i][j] == 'E')
            {
                data->player.x = j;
                data->player.y = i;
                set_dir(data->player, data->map[i][j]);
                return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

int     check_data(t_data *data)
{
    if (!data->north || !data->south || !data->west || !data->east)
    {
        ft_putendl_fd("Error: missing wall texture.", 2);
        return(0);
    }
    if (data->floor.red == -1 || data->ceiling.red == -1)
    {
        ft_putendl_fd("Error: missing floor or ceiling color.", 2);
        return(0);
    }
    if (!data->map[0])
    {
        ft_putendl_fd("Error: invalid map.", 2);
        return(0);
    }
    if (!check_player(data))
    {
        ft_putendl_fd("Error: missing player start point.", 2);
        return(0);
    }
}
