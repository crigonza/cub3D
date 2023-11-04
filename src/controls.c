#include "../inc/cub3d.h"

void move_forward(t_game *game)
{
    double newPosX;
    double newPosY;

    newPosX = game->player.pos_x + game->player.dir_x * game->player.speed;
    newPosY = game->player.pos_y + game->player.dir_y * game->player.speed;
    if (game->map.map_array[(int)game->player.pos_y][(int)newPosX] != '1')
        game->player.pos_x = newPosX;
    if (game->map.map_array[(int)newPosY][(int)game->player.pos_x] != '1')
        game->player.pos_y = newPosY;
}

void move_backward(t_game *game)
{
    double newPosX;
    double newPosY;

    newPosX = game->player.pos_x - game->player.dir_x * game->player.speed;
    newPosY = game->player.pos_y - game->player.dir_y * game->player.speed;
    if (game->map.map_array[(int)game->player.pos_y][(int)newPosX] != '1')
        game->player.pos_x = newPosX;
    if (game->map.map_array[(int)newPosY][(int)game->player.pos_x] != '1')
        game->player.pos_y = newPosY;
}

void move_right(t_game *game)
{
    double newPosX;
    double newPosY;

    newPosX = game->player.pos_x - game->player.dir_y * game->player.speed;
    newPosY = game->player.pos_y + game->player.dir_x * game->player.speed;
    if (game->map.map_array[(int)game->player.pos_y][(int)newPosX] != '1')
        game->player.pos_x = newPosX;
    if (game->map.map_array[(int)newPosY][(int)game->player.pos_x] != '1')
        game->player.pos_y = newPosY;
}

void move_left(t_game *game)
{
    double newPosX;
    double newPosY;

    newPosX = game->player.pos_x + game->player.dir_y * game->player.speed;
    newPosY = game->player.pos_y - game->player.dir_x * game->player.speed;
    if (game->map.map_array[(int)game->player.pos_y][(int)newPosX] != '1')
        game->player.pos_x = newPosX;
    if (game->map.map_array[(int)newPosY][(int)game->player.pos_x] != '1')
        game->player.pos_y = newPosY;
}

void rotate_right(t_player *player)
{
    double  old_dir_x;
    double  old_plane_x;

    old_dir_x = player->dir_x;
    old_plane_x = player->plane_x;
    player->dir_x = player->dir_x * cos(player->rotate_speed) - player->dir_y * sin(player->rotate_speed);
    player->dir_y = old_dir_x * sin(player->rotate_speed) + player->dir_y * cos (player->rotate_speed);
    player->plane_x  = player->plane_x * cos(player->rotate_speed) - player->plane_y * sin(player->rotate_speed);
    player->plane_y  = old_plane_x * sin(player->rotate_speed) + player->plane_y * cos(player->rotate_speed);
}

void rotate_left(t_player *player)
{
    double  old_dir_x;
    double  old_plane_x;

    old_dir_x = player->dir_x;
    old_plane_x = player->plane_x;
    player->dir_x = player->dir_x * cos(-player->rotate_speed) - player->dir_y * sin(-player->rotate_speed);
    player->dir_y = old_dir_x * sin(-player->rotate_speed) + player->dir_y * cos (-player->rotate_speed);
    player->plane_x  = player->plane_x * cos(-player->rotate_speed) - player->plane_y * sin(-player->rotate_speed);
    player->plane_y  = old_plane_x * sin(-player->rotate_speed) + player->plane_y * cos(-player->rotate_speed);
}