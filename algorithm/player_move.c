/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:05:53 by sechlahb          #+#    #+#             */
/*   Updated: 2025/11/30 21:38:53 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int is_wall_pixel(t_game *game, int x, int y)
{
    int map_x = (int)(x / tile_size);
    int map_y = (int)(y / tile_size);
    if (map_y < 0 || map_y >= game->map.height || map_x < 0 || map_x >= game->map.width)
        return (1);
    if (map_y < ft_strlen(game->map.layout[map_y]) && game->map.layout[map_y][map_x] == '1')
        return (1);
    return 0;
}

int player_movment(int key, void *arg)
{
    t_game *game;
    double new_x;
    double new_y;
    double old_dir_x;
    double old_dir_y;
    double sinr, cosr;

    game = (t_game *)arg;
    if (esc == key)
        exit (0);

    if (key == w_key || key == up_key)
    {
        new_x = game->player.pos_x + MOVE_SPEED * game->player.dir_y; 
        new_y = game->player.pos_y - MOVE_SPEED * game->player.dir_x;
        if (!is_wall_pixel(game, new_x, game->player.pos_y))
            game->player.pos_x = new_x;
        if (!is_wall_pixel(game, game->player.pos_x, new_y))
            game->player.pos_y = new_y;
    }
    if (key == s_key || key == down_key)
    {
        new_x = game->player.pos_x - game->player.dir_y * MOVE_SPEED;
        new_y = game->player.pos_y + game->player.dir_x * MOVE_SPEED;
        if (!is_wall_pixel(game, new_x, game->player.pos_y))
            game->player.pos_x = new_x;
        if (!is_wall_pixel(game, game->player.pos_x, new_y))
            game->player.pos_y = new_y;
    }

    if (key == d_key)
    {
        new_x = game->player.pos_x + MOVE_SPEED * game->player.dir_x; 
        new_y = game->player.pos_y + MOVE_SPEED * game->player.dir_y;
        if (!is_wall_pixel(game, new_x, game->player.pos_y))
            game->player.pos_x = new_x;
        if (!is_wall_pixel(game, game->player.pos_x, new_y))
            game->player.pos_y = new_y;
    }
    if (key == a_key)
    {
        new_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
        new_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
        if (!is_wall_pixel(game, new_x, game->player.pos_y))
            game->player.pos_x = new_x;
        if (!is_wall_pixel(game, game->player.pos_x, new_y))
            game->player.pos_y = new_y;
    }
    


    
    if (key == right_key) // rotate left
    {
        old_dir_x = game->player.dir_x;
        old_dir_y = game->player.dir_y;
        cosr = cos(ROT_SPEED);
        sinr = sin(ROT_SPEED);
        game->player.dir_x = old_dir_x * cosr - old_dir_y * sinr;
        game->player.dir_y = old_dir_x * sinr + old_dir_y * cosr;
    }
    if (key == left_key) // rotate right
    {
        old_dir_x = game->player.dir_x;
        old_dir_y = game->player.dir_y;
        cosr = cos(-ROT_SPEED);
        sinr = sin(-ROT_SPEED);
        game->player.dir_x = old_dir_x * cosr - old_dir_y * sinr;
        game->player.dir_y = old_dir_x * sinr + old_dir_y * cosr;
    }
    return key;
}