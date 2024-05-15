/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_valid_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:33:13 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/13 19:35:11 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static int	is_char_valid(t_tilemap *map, int pos_x, int pos_y);
static int	is_map_beatable(t_tilemap *map, t_vector *p_start_pos);
static void	all_collectibles_collected(t_tile **map, int x,
				int y, int *collectible_p);
static t_tile	**duplicate_matrix(t_tilemap *map);

int	is_map_valid(t_tilemap *map)
{
	int	y;
	int	x;
	int	checks;

	map->collectible_am = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			checks = is_char_valid(map, x, y);
			if (checks == -1)
				return (free_matrix(map->matrix), exit(0), FALSE);
		}
	}
	if (checks != 7)
		return (ft_printf(INVALID_MAP_ERROR),
			free_matrix(map->matrix), exit(0), FALSE);
	if (!is_map_beatable(map, &map->p_start_pos))
		return (FALSE);
	return (TRUE);
}

static int	is_char_valid(t_tilemap *map, int pos_x, int pos_y)
{
	static int	checks;
	char		c;

	c = map->matrix[pos_y][pos_x].c;
	if ((pos_y == 0 || pos_y == map->height - 1
			|| pos_x == 0 || pos_x == map->width - 1)
		&& c != '1')
		return (ft_printf(INVALID_MAP_ERROR), -1);
	else if (c == 'P' && checks % 2 == 0)
		return (checks |= 1,
			map->p_start_pos.x = pos_x,
			map->p_start_pos.y = pos_y,
			checks);
	else if (c == 'E' && checks < 4)
		return (checks |= 1 << 2, checks);
	else if (c == 'C')
		return (checks |= 1 << 1, map->collectible_am++, checks);
	else if (c == '1' || c == '0')
		return (checks);
	else
		return (ft_printf(INVALID_MAP_ERROR), -1);
}

static int	is_map_beatable(t_tilemap *map, t_vector *p_start_pos)
{
	t_tile	**map_dup;
	int		collectible_p;

	collectible_p = 0;
	map_dup = duplicate_matrix(map);
	if (!map_dup)
		return (ft_printf(ALLOC_ERROR), FALSE);
	all_collectibles_collected(map_dup, p_start_pos->x,
		p_start_pos->y, &collectible_p);
	if (collectible_p != map->collectible_am + 1)
		return (free_matrix(map_dup), free_matrix(map->matrix),
			ft_printf(INVALID_MAP_ERROR), exit(0), FALSE);
	if (map->width > MAX_WIDTH || map->height > MAX_HEIGHT)
		printf("Map exceeds screen measures! It will still be processed, \
			but some tiles will may be hidden.\n");
	return (free_matrix(map_dup), TRUE);
}

static void	all_collectibles_collected(t_tile **map, int x,
		int y, int *collectible_p)
{
	if (map[y][x].c == 'F' || map[y][x].c == '1')
		return ;
	if (map[y][x].c == 'C' || map[y][x].c == 'E')
		*collectible_p += 1;
	map[y][x].c = 'F';
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
