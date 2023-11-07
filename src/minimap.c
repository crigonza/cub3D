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

    y = 5;
    while (y < game->map.map_h + 5)
    {
        x = 5;
        while (game->map.map_array[y - 5][x - 5])
        {
            if (game->map.map_array[y - 5][x - 5] == '1')
                minimap_square(game, TILE * x, TILE * y, get_rgba(150, 150, 150, 0xFF));
            else if (game->map.map_array[y - 5][x - 5] == 'S' || game->map.map_array[y - 5][x - 5] == 'N' || 
                    game->map.map_array[y - 5][x - 5] == 'W' || game->map.map_array[y - 5][x - 5] == 'E')
                    minimap_square(game, TILE * x, TILE * y, get_rgba(10, 99, 71,254));
            /* else
                minimap_square(game, TILE * x, TILE * y, get_rgba(100, 100, 100, 0x00)); */
            x++;
        }
        y++;
    }
    minimap_player(game, TILE * game->player.pos_x, TILE * game->player.pos_y, get_rgba(200, 100, 100, 0xFF));
}

void    minimap_player(t_game *game, int x, int y, int color)
{
    int dx;
    int dy;
    int x_e;
    int y_e;
 
    dy = 0;
    while (dy < TILE)
    {
        dx = 0;
        while (dx < TILE)
        {
            mlx_put_pixel(game->img, dy + x + 5, dx + y + 5, color);
            dx++;
        }
        dy++;
    } 
    printf("%f %f %f %f\n",game->player.dir_x, game->player.dir_y,game->player.plane_x, game->player.plane_y);
    x_e = game->player.pos_x * TILE + cos(game->player.rotate_speed) * TILE * 10;
    y_e = game->player.pos_y * TILE + sin(game->player.rotate_speed) * TILE * 10;
    //draw_vec(game, x+5, y+5, x+5, TILE * (game->player.pos_y- 0.5) + 20,color);
    //draw_vec(game, x+5, y+5, x_e, y_e,color);
}