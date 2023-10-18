/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 19:56:19 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/18 21:00:44 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int checknl(char *s)
{
    if (!s)
        return(0);
    while(*s)
    {
        if (*s == '\n')
            return(1);
        s++;
    }
    return (0);
}

char *get_line(char *st)
{
    int i = 0;
    char *line;

    if (!st[0])
        return(NULL);
    while (st[i] && st[i] != '\n')
        i++;
    if (st[i] == '\n')
        i++;
    line = ft_calloc(i + 1, sizeof(char));
    i = 0;
    while (st[i] && st[i] != '\n')
    {
        line[i] = st[i];
        i++;
    }    
    if (st[i] == '\n')
        line[i] = '\n';
    return (line);
}

char *get_st(char *st)
{
    int i = 0;
    int j = 0;
    char *new;

    if (!st)
        return(NULL);
    while(st[i] && st[i] != '\n')
        i++;
    if (st[i] == '\0')
        return(free(st), NULL);
    i++;
    new = ft_calloc((ft_strlen(st) - i) + 1, sizeof(char));
    while(st[i])
        new[j++] = st[i++];
    free(st);
    return (new);
}

char    *get_next_line(int fd)
{
    static char     *stach;
    char            *line;
    char            buffer[5];
    int             rd;

    rd = 1;
    stach = NULL;
    line = NULL;
    if (fd < 0)
        return (NULL);
    while (rd > 0 && checknl(stach) == 0)
    {
        rd = read(fd, buffer, 5);
        if (rd == -1)
        {
            free (stach);
            return (NULL);
        }
        buffer[rd] = '\0';
        stach = ft_strjoin(stach, buffer);
    }
    line = get_line(stach);
    stach = get_st(stach);
    return(line);
}
