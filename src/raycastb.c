/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 10:35:48 by crigonza          #+#    #+#             */
/*   Updated: 2023/10/29 11:16:01 by crigonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/* void    verLine(t_info *info, int x, int y1, int y2, int color)
{
    int y;

    y = y1;
    while (y <= y2)
    {
        mlx_put_pixel(info->screen, x, y, color);
        y++;
    }
    
}


void    calc(t_info *info)
{
    int x;
    x = 0;
    while (x < width)
    {
        double cameraX = 2 * x / (double)width - 1;
        double rayDirX = info->dirX + info->planeX * cameraX;
        double rayDirY = info->dirY + info->planeY * cameraX;
        
        int mapX = (int)info->posX;
        int mapY = (int)info->posY;

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;
        
         //length of ray from one x or y-side to next x or y-side
        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;
        
        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;
        
        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (info->posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - info->posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (info->posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - info->posY) * deltaDistY;
        }

        while (hit == 0)
        {
            //jump to next map square, OR in x-direction, OR in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (worldMap[mapX][mapY] > 0) hit = 1;
        }
        if (side == 0)
            perpWallDist = (mapX - info->posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - info->posY + (1 - stepY) / 2) / rayDirY;

        //Calculate height of line to draw on screen
        int lineHeight = (int)(height / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + height / 2;
        if(drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + height / 2;
        if(drawEnd >= height)
            drawEnd = height - 1;

        int color;
        if (worldMap[mapY][mapX] == 1)
            color = 0x4EF4F4;
        else if (worldMap[mapY][mapX] == 2)
            color = 0xF4764E;
        else if (worldMap[mapY][mapX] == 3)
            color = 0x5B4EF4;
        else if (worldMap[mapY][mapX] == 4)
            color = 0x20E647;
        else
            color = 0xE620D4;
        
        if (side == 1)
            color = color / 2;
        verLine(info, x, drawStart, drawEnd, color);
        x++;
    }
}

void    main_loop(void *param)
{
    t_info  *info;

    info = param;
    if (info->screen)
        mlx_delete_image(info->mlx,info->screen);
    info->screen = mlx_new_image(info->mlx, width, height);
    mlx_image_to_window(info->mlx,info->screen,0,0);
    calc(info);
}

void    my_keyhook(mlx_key_data_t keydata, void *param)
{
    t_info  *info;

    info = param;
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        exit(0);
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
            {
        if (!worldMap[(int)(info->posX + info->dirX * info->moveSpeed)][(int)(info->posY)])
            info->posX += info->dirX * info->moveSpeed;
        if (!worldMap[(int)(info->posX)][(int)(info->posY + info->dirY * info->moveSpeed)])
            info->posY += info->dirY * info->moveSpeed;
    }
    if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
        {
        if (!worldMap[(int)(info->posX - info->dirX * info->moveSpeed)][(int)(info->posY)])
            info->posX -= info->dirX * info->moveSpeed;
        if (!worldMap[(int)(info->posX)][(int)(info->posY - info->dirY * info->moveSpeed)])
            info->posY -= info->dirY * info->moveSpeed;
    }
    if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
            {
        //both camera direction and camera plane must be rotated
        double oldDirX = info->dirX;
        info->dirX = info->dirX * cos(info->rotSpeed) - info->dirY * sin(info->rotSpeed);
        info->dirY = oldDirX * sin(info->rotSpeed) + info->dirY * cos(info->rotSpeed);
        double oldPlaneX = info->planeX;
        info->planeX = info->planeX * cos(info->rotSpeed) - info->planeY * sin(info->rotSpeed);
        info->planeY = oldPlaneX * sin(info->rotSpeed) + info->planeY * cos(info->rotSpeed);
    }
    if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
    {
                //both camera direction and camera plane must be rotated
        double oldDirX = info->dirX;
        info->dirX = info->dirX * cos(-info->rotSpeed) - info->dirY * sin(-info->rotSpeed);
        info->dirY = oldDirX * sin(-info->rotSpeed) + info->dirY * cos(-info->rotSpeed);
        double oldPlaneX = info->planeX;
        info->planeX = info->planeX * cos(-info->rotSpeed) - info->planeY * sin(-info->rotSpeed);
        info->planeY = oldPlaneX * sin(-info->rotSpeed) + info->planeY * cos(-info->rotSpeed);
    }
} */


/* int main(void)
{
    t_info info;
    info.mlx = mlx_init(width, height, "mlx42",true);

    info.posX = 12;
    info.posY = 5;
    info.dirX = -1;
    info.dirY = 0;
    info.planeX = 0;
    info.planeY = 0.66;
    info.moveSpeed = 0.05;
    info.rotSpeed = 0.05;
    
    mlx_loop_hook(info.mlx, main_loop, &info);
    mlx_key_hook(info.mlx, my_keyhook, &info);
    mlx_loop(info.mlx);
} */