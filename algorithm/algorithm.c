/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/09/28 13:19:41 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_game *fill_data(t_map *data)
{
    t_game *game;

    game = gc_malloc(sizeof(t_game), data);
    ft_memset(game, 0, sizeof(t_game));
    game->map.layout = data->map;
    game->map.width = data->max_len;
    game->map.height = data->height;

    // texters save
    game->map.no_texture = data->map_info->no;
    game->map.so_texture = data->map_info->so;
    game->map.we_texture = data->map_info->we;
    game->map.ea_texture = data->map_info->ea;

    game->map.floor_color = data->map_info->f;
    game->map.ceil_color = data->map_info->c;

    game->player.pos_x = data->p_x;
    game->player.pos_y = data->p_y;
    return (game);
}

int handel_exit(void *data)
{
    (void)data;
    exit(1);
}

void algorithm(t_map *data)
{
    t_game *game;

    game = fill_data(data);
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, SCREEN_W, SCREEN_H , "cub3d");
    mlx_hook(game->win, 17, 0, handel_exit, NULL);
    // mlx_hook(game->window, 2, 1L<<0, player_movment, game);
    // // mlx_loop_hook(game->mlx, rander_map, game);
    mlx_loop(game->mlx);
}