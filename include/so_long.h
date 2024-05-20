/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:39:00 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/20 13:37:29 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx_int.h"
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <stdlib.h>
# include <errno.h>
# include <time.h>

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

typedef struct s_tile
{
	char	c;
	int		anim;
}	t_tile;

typedef struct s_sprite
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_sprite;

typedef struct s_tilemap
{
	int			width;
	int			height;
	t_tile		**matrix;
	int			collectible_am;
	int			available_space;
	t_vector	p_start_pos;
}	t_tilemap;

typedef struct s_entity
{
	t_vector	pos;
	t_vector	p_pos;
	t_sprite	*sprite;
	int			mov_am;
	int			max_mov_am;
	int			mov_dir;
}	t_entity;

typedef struct s_root
{
	void			*mlx;
	void			*win;
	t_tilemap		map;
	t_sprite		*world_sprite;
	t_entity		player;
	int				input_allowed;
	unsigned int	global_timer;
}	t_root;

# define WRONG_USAGE_ERROR "Error\n Wrong usage"
# define WRONG_EXTENSION_ERROR "Error\n File is not .ber\n"
# define WIDTH_ERROR "Error\n Map is not rectangular"
# define ALLOC_ERROR "Error\n Allocation failure\n"
# define INVALID_PATH_ERROR "Error\n Provided map path is invalid\n"
# define INVALID_MAP_ERROR "ERROR\n Provided map is invalid\n"
# define MAP_TOO_BIG_WARNING "WARNING\n Map exceeds screen measures! \
It will still be processed, but some tiles may be hidden.\n"

# define WIN_MSG "You saved everyone and managed to escape!!\n"
# define LOSE_MSG "You ran out of stamina and fell off the mountain!\n"

# define TRUE 1
# define FALSE 0

# define PLAYER_FLAG 0
# define COLLECT_FLAG 1
# define EXIT_FLAG 2

# define PROGRAM_NAME "so_long"

# define FLOOD 'F'
# define EMPTY '0'
# define STD_EMPTY_PATH "./sprites_bonus/empty/empty0.xpm"
# define EMPTY_PATH "./sprites_bonus/empty/empty"
# define WALL '1'
# define WALL_PATH "./sprites_bonus/wall/wall.xpm"
# define COLLECTIBLE 'C'
# define COLLECTIBLE_PATH "./sprites_bonus/collectible/collectible0.xpm"
# define COLLECTIBLE_PATH_HELP "./sprites_bonus/collectible/collectible1.xpm"
# define EXIT 'E'
# define EXIT_PATH "./sprites_bonus/exit/exit.xpm"
# define PLAYER 'P'
# define STD_PLAYER_PATH "./sprites_bonus/player/player0.xpm"
# define PLAYER_STANDING_PATH "./sprites_bonus/player/player00.xpm"
# define PLAYER_PATH "./sprites_bonus/player/player"
# define RAIN_PATH "./sprites_bonus/rain/rain"
# define BALOON_PATH "./sprites_bonus/baloon.xpm"
# define IMG_EXTENSION ".xpm"
# define MAP_EXTENSION ".ber"
# define MAP_EXTENSION_LEN 4

# define STILL 0
# define UP 1
# define RIGHT 2
# define DOWN 3
# define LEFT 4

# define WHITE 0xFFFFFF
# define MAX_COLOR 0xFF
# define MAX_WIDTH 30
# define MAX_HEIGHT 14
# define FPS 10
# define SECOND 1000000000
# define SPRITE_SIZE 64
# define BITE_SIZE 8

void			parse_map(t_root *root, char *map_filename);
void			check_map_validity(t_tilemap *map);
int				render_next_frame(t_root *root);
void			handle_player_mov(t_root *root);

char			*get_sprite_path(t_root *root, t_tile tile);
t_sprite		*create_sprite(t_root *root, char *sprite_path);
void			put_sprite_in_world(t_sprite *sprite, t_root *root,
					int posx, int posy);
void			put_player_anim_in_world(t_sprite *sprite, t_root *root,
					int posx, int posy);

char			*get_empty_frame(t_tile tile, int timer);
char			*get_player_frame(int dir);
char			*get_collectible_frame(t_tile tile);

void			put_map(t_root *root);
void			put_player(t_root *root);
void			put_collectibles(t_root *root);

void			put_pixel(t_sprite *sprite, int x, int y, int color);
unsigned int	get_color_in_pixel(t_sprite *sprite, int x, int y);
int				get_player_color(t_entity *player);

void			close_game_at_parsing(int fd, t_tilemap *map, char *error_msg);
int				close_game(t_root *root);
void			free_matrix(t_tile **matrix);

#endif
