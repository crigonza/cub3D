/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 18:29:04 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/18 19:54:18 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void    parser(t_data *data, char *file)
{
    
}

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
        return(0);
    }
    fd = open(argv[1], argc);
    if (fd == -1)
    {
        ft_putendl_fd("Error: cant open archive.", 2);
        close (fd);
        return (0);
    }
    close (fd);
    return(1);
}

int main(int argc, char **argv)
{
    t_data  *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!check_args(argc, argv));
        exit(EXIT_FAILURE);
    parser(data, argv[1]);

    system("leaks --q fdf");
    exit (EXIT_SUCCESS);
}