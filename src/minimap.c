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

void    minimap_player(t_game *game, int x, int y, int color)
{
    int dx;
    int dy;
 
    dy = 0;
    while (dy < TILE)
    {
        dx = 0;
        while (dx < TILE)
        {
            mlx_put_pixel(game->img, dy + x, dx + y, color);
            dx++;
        }
        dy++;
    } 
}
 
void    minimap_squares(t_game *game)
{
    int x;
    int y;

    y = 5;
    while (y < game->map.map_h + 5)
    {
        x = 5;
        while (game->map.map_array[y - 5][x - 5])
        {
            if (game->map.map_array[y - 5][x - 5] == '1')
                minimap_square(game, TILE * x, TILE * y, get_rgba(200, 200, 200, 0xFF));
            x++;
        }
        y++;
    }
    minimap_player(game, TILE * (int)(game->player.pos_x + 5), TILE * (int)(game->player.pos_y + 5), get_rgba(200, 100, 100, 0xFF));
}
