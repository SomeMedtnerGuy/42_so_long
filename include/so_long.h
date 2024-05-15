/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:39:00 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/13 17:03:33 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx_int.h"
# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"

typedef struct s_vector
{
	int	x;
	int	y;
}	t_vector;

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
	char		**matrix;
	int			collectible_am;
	t_vector	p_start_pos;
}	t_tilemap;

typedef struct s_entity
{
	t_vector	pos;
	t_sprite	*sprite;
	int			mov_am;
}	t_entity;

typedef struct s_root
{
	void			*mlx;
	void			*win;
	t_tilemap		map;
	t_sprite		*world_sprite;
	t_entity		player;
	unsigned int	global_timer;
}	t_root;

# define TRUE 1
# define FALSE 0

# define EMPTY '0'
# define EMPTY_PATH "./sprites/empty.xpm"
# define WALL '1'
# define WALL_PATH "./sprites/wall.xpm"
# define COLLECTIBLE 'C'
# define COLLECTIBLE_PATH "./sprites/collectible.xpm"
# define EXIT 'E'
# define EXIT_PATH "./sprites/exit.xpm"
# define PLAYER 'P'
# define PLAYER_PATH "./sprites/player.xpm"

# define MAX_WIDTH 30
# define MAX_HEIGHT 14
# define FPS 30
# define SPRITE_SIZE 64

# define WRONG_USAGE_ERROR "Error\n Wrong usage"
# define WRONG_EXTENTION_ERROR "Error\n File is not .ber\n"
# define WIDTH_ERROR "Error\n Width discrepancy noticed in line %i\n"
# define ALLOC_ERROR "Error\n Allocation failure\n"
# define INVALID_PATH_ERROR "Error\n Provided map path is invalid\n"
# define INVALID_MAP_ERROR "ERROR\n Provided map is invalid\n"

int				is_map_valid(t_tilemap *map);
void			parse_map(t_root *root, char *map_filename);
void			put_pixel(t_sprite *sprite, int x, int y, int color);
unsigned int	get_color_in_pixel(t_sprite *sprite, int x, int y);
char			*get_sprite_path(char component);
t_sprite		*create_sprite(t_root *root, char *sprite_path);
void			put_sprite_in_world(t_sprite *sprite,
					t_root *root, int posx, int posy);
void			put_map(t_root *root);
void			put_player(t_root *root);
void			put_collectibles(t_root *root);
void			update_frame(t_root *root);
void			handle_player_mov(t_root *root);
int				close_game(t_root *root);
void			free_matrix(char **matrix);
void			free_map_and_exit(t_tilemap *map);

#endif
