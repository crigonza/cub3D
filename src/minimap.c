#include "../inc/cub3d.h"

/*void    minimap_circle(t_game *game, int x, int y, int color)
{
    double i;
    double angle;
    double dx;
    double dy;
 
    i = 0;
    while (i < 360)
    {
        angle = i;
        dx = TILE * cos((angle * PI) / 180);
        dy = TILE * sin((angle * PI) / 180);
        mlx_put_pixel(game->img, (int)dx + x, (int)dy + y, color);
        i += 0.1;
    }
}*/

void    minimap_square(t_game *game, int x, int y, int color)
{
    int dx;
    int dy;
 
    dy = 0;
    while (dy < TILE)
    {
        dx = 0;
        while (dx < TILE)
        {
            mlx_put_pixel(game->img, dx + x, dy + y, color);
            dx++;
        }
        dy++;
    }
}
 
void    minimap_squares(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map.map_h)
    {
        x = 0;
        while (x < game->map.map_w)
        {
            if (game->map.map_array[y][x] == '1')
                minimap_square(game, TILE * x, TILE * y, get_rgba(10, 10, 10, 10));
            else if (game->map.map_array[y][x] == 'S' || game->map.map_array[y][x] == 'N' || 
                    game->map.map_array[y][x] == 'W' || game->map.map_array[y][x] == 'E')
                    minimap_square(game, TILE * x, TILE * y, get_rgba(10, 99, 71,254));
            else
                minimap_square(game, TILE * x, TILE * y, get_rgba(10, 88, 235, 196));
            x++;
        }
        y++;
    }
}