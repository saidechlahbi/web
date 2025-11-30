/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d2.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 18:31:42 by sechlahb          #+#    #+#             */
/*   Updated: 2025/11/30 21:40:53 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D2_H
# define CUB3D2_H
// #include "/mnt/c/Users/DELL/OneDrive/Bureau/42 school cersus/1337-Common-core/minilibx-linux/mlx.h"
# include "/home/sechlahb/Desktop/minilibx-linux/mlx.h"
// #include "cub3d.h"



#define RAY_FOV (60.0 * M_PI / 180.0)  // 60 degrees converted to radians
#define NUM_RAYS 240                   // number of rays to cast across FOV
#define MAX_RAY_DISTANCE 2000.0        // max distance a ray can travel (in pixels)
#define RAY_STEP 1.0                   // ray marching step (in pixels)
#define PLAYER_SIZE 6                  // player radius for drawing
#define COLOR_BG 0x1E1E1E
#define COLOR_WALL 0x888888
#define COLOR_EMPTY 0x2E2E2E
#define COLOR_RAY 0xFFFF00
#define COLOR_PLAYER 0x00FF00

#define MOVE_SPEED 4.0        // pixels per key press
#define ROT_SPEED (5.0 * M_PI / 180.0) // 5 degrees in radians

#define SCREEN_W 670
#define SCREEN_H 670

# define w_key 119
# define a_key 97
# define s_key 115
# define d_key 100
# define  esc 65307

# define up_key 65362
# define left_key 65361
# define down_key 65364
# define right_key 65363

# define tile_size 32
// # define FOV 60

typedef struct s_player
{
    double  pos_x;
    double  pos_y;
    double  dir_x; 
    double  dir_y;
    double  plane_x;
    double  plane_y;
}   t_player;


typedef struct s_img
{
    void    *img;
    char    *addr;
    int     bpp;
    int     line_len;
    int     endian;
    int     width;
    int     height;
}   t_img;

typedef struct s_maps
{
    char    **layout;
    int     width;
    int     height;
    char    *no_texture;
    char    *so_texture;
    char    *we_texture;
    char    *ea_texture;
    int     *floor_color;
    int     *ceil_color;
}   t_maps;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_img       screen;
    t_maps       map;
    t_player    player;
}   t_game;


/*--------------raycasting----------------*/
// void algorithm(t_map *game);


#endif