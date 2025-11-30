/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rander_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:28:22 by sechlahb          #+#    #+#             */
/*   Updated: 2025/11/30 18:59:08 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <math.h>

void put_pixel(t_img* screen, int x, int y, int color)
{
    char *pixel;
    
    if (x < 0 || x >= SCREEN_W || y < 0 || y >= SCREEN_H)
        return;
    pixel = screen->addr + (y * screen->line_len  + x * (screen->bpp / 8));
    *(unsigned int *)pixel = (unsigned int)color;
}

void clear_screen(t_img *screen, int color)
{
    int x;
    int y;

    y = 0;
    while (y < SCREEN_H)
    {
        x = 0;
        while (x < SCREEN_W)
        {
            put_pixel(screen, x, y, color);
            x++;
        }
        y++;
    }
}

void draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
    int i, j;

    i = 0;
    while (i < h)
    {
        j = 0;
        while (j < w)
        {
            put_pixel(img, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void draw_map_topdown(t_game *game)
{
    int row, col;
    int px, py;
    char c;
    int tile = tile_size;

    row = 0;
    while (row < game->map.height)
    {
        col = 0;
        while (col < game->map.width)
        {
            // some map rows may be shorter: guard
            c = ' ';
            if (row < game->map.height && col < (int)ft_strlen(game->map.layout[row]))
                c = game->map.layout[row][col];

            px = col * tile;
            py = row * tile;
            if (c == '1')
                draw_rect(&game->screen, px, py, tile, tile, COLOR_WALL);
            else
                draw_rect(&game->screen, px, py, tile, tile, COLOR_EMPTY);
            col++;
        }
        row++;
    }
}

static int is_wall_pixel(t_game *game, double x, double y)
{
    int map_x = (int)(x / tile_size);
    int map_y = (int)(y / tile_size);

    if (map_y < 0 || map_y >= game->map.height || map_x < 0 || map_x >= game->map.width)
        return (1); // out-of-bounds treated as wall for safety

    if (map_y < (int)ft_strlen(game->map.layout[map_y]) && game->map.layout[map_y][map_x] == '1')
        return (1);

    return (0);
}

void cast_and_draw_rays(t_game *game)
{
    int i;
    double half_fov = RAY_FOV / 2.0;
    double base_angle = atan2(game->player.dir_y, game->player.dir_x);
    double angle_step = RAY_FOV / (double)NUM_RAYS;
    double angle;
    double rx, ry;
    double dist;
    int steps;
    // int sx, sy;

    i = 0;
    while (i < NUM_RAYS)
    {
        angle = base_angle - half_fov + i * angle_step;
        // normalize angle optional
        rx = game->player.pos_x;
        ry = game->player.pos_y;
        dist = 0.0;
        steps = 0;
        while (dist < MAX_RAY_DISTANCE)
        {
            rx += cos(angle) * RAY_STEP;
            ry += sin(angle) * RAY_STEP;
            dist += RAY_STEP;
            steps++;

            if (is_wall_pixel(game, rx, ry))
            {
                // draw the hit pixel as bright (small dot)
                put_pixel(&game->screen, (int)rx, (int)ry, 0xFF4400);
                break;
            }
            // optionally draw the ray path (thin)
            put_pixel(&game->screen, (int)rx, (int)ry, COLOR_RAY);
        }
        i++;
    }
}

void draw_player(t_game *game)
{
    int x = (int)game->player.pos_x;
    int y = (int)game->player.pos_y;
    int s = PLAYER_SIZE;
    int i, j;

    i = -s;
    while (i <= s)
    {
        j = -s;
        while (j <= s)
        {
            put_pixel(&game->screen, x + j, y + i, COLOR_PLAYER);
            j++;
        }
        i++;
    }
}

int rander_map(t_game *game)
{
    // clear screen
    clear_screen(&game->screen, COLOR_BG);

    // 2) Draw map top-down
    draw_map_topdown(game);

    // 3) Cast and draw rays from player
    cast_and_draw_rays(game);
    
    // 4) Draw player
    draw_player(game);

    mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
    return 0;
}