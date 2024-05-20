/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:33:13 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/19 11:05:40 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int		is_char_valid(t_tilemap *map, int pos_x, int pos_y);
static void		check_beatability(t_tilemap *map, t_vector *p_start_pos);
static void		all_collectibles_collected(t_tile **map, int x,
					int y, int *collectible_p);
static t_tile	**duplicate_matrix(t_tilemap *map);

void	check_map_validity(t_tilemap *map)
{
	int	y;
	int	x;
	int	checks;

	map->collectible_am = 0;
	map->available_space = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			checks = is_char_valid(map, x, y);
			if (checks == -1)
				close_game_at_parsing(0, map, INVALID_MAP_ERROR);
		}
	}
	if (checks != 7)
		close_game_at_parsing(0, map, INVALID_MAP_ERROR);
	check_beatability(map, &map->p_start_pos);
}

static int	is_char_valid(t_tilemap *map, int pos_x, int pos_y)
{
	static int	checks;
	char		c;

	c = map->matrix[pos_y][pos_x].c;
	if ((pos_y == 0 || pos_y == map->height - 1
			|| pos_x == 0 || pos_x == map->width - 1)
		&& c != WALL)
		return (-1);
	else if (c == PLAYER && !(checks & 1 << PLAYER_FLAG))
		return (checks |= 1 << PLAYER_FLAG, map->available_space += 1,
			map->p_start_pos.x = pos_x,
			map->p_start_pos.y = pos_y,
			checks);
	else if (c == EXIT && !(checks & 1 << EXIT_FLAG))
		return (map->available_space += 1, checks |= 1 << EXIT_FLAG, checks);
	else if (c == COLLECTIBLE)
		return (map->available_space += 1, checks |= 1 << COLLECT_FLAG,
			map->collectible_am++, checks);
	else if (c == EMPTY)
		return (map->available_space += 1, checks);
	else if (c == WALL)
		return (checks);
	return (-1);
}

static void	check_beatability(t_tilemap *map, t_vector *p_start_pos)
{
	t_tile	**map_dup;
	int		collectible_p;

	collectible_p = 0;
	map_dup = duplicate_matrix(map);
	if (!map_dup)
		close_game_at_parsing(0, map, ALLOC_ERROR);
	all_collectibles_collected(map_dup, p_start_pos->x,
		p_start_pos->y, &collectible_p);
	if (collectible_p != map->collectible_am + 1)
	{
		free_matrix(map_dup);
		close_game_at_parsing(0, map, INVALID_MAP_ERROR);
	}
	if (map->width > MAX_WIDTH || map->height > MAX_HEIGHT)
		printf(MAP_TOO_BIG_WARNING);
	free_matrix(map_dup);
}

static void	all_collectibles_collected(t_tile **map, int x,
		int y, int *collectible_p)
{
	if (map[y][x].c == FLOOD || map[y][x].c == WALL)
		return ;
	if (map[y][x].c == COLLECTIBLE || map[y][x].c == EXIT)
		*collectible_p += 1;
	map[y][x].c = FLOOD;
	all_collectibles_collected(map, x + 1, y, collectible_p);
	all_collectibles_collected(map, x - 1, y, collectible_p);
	all_collectibles_collected(map, x, y + 1, collectible_p);
	all_collectibles_collected(map, x, y - 1, collectible_p);
}

static t_tile	**duplicate_matrix(t_tilemap *map)
{
	t_tile	**matrix;
	int		y;
	int		x;

	y = -1;
	matrix = (t_tile **)ft_calloc(map->height + 1, sizeof(t_tile *));
	if (!matrix)
		return (NULL);
	while (++y < map->height)
	{
		x = -1;
		matrix[y] = ft_calloc(map->width + 1, sizeof(t_tile));
		if (!matrix[y])
			return (free_matrix(matrix), NULL);
		while (++x < map->width)
			matrix[y][x].c = map->matrix[y][x].c;
	}
	return (matrix);
}
