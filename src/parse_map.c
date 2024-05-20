/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:34:14 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/19 09:48:23 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static void	get_map_size(t_root *root, char *map_filename);
static void	alloc_map(t_tilemap *map);
static void	import_map(t_tilemap *map, char *map_filename);

void	parse_map(t_root *root, char *map_filename)
{
	if (ft_strncmp(MAP_EXTENSION,
			map_filename + (ft_strlen(map_filename) - MAP_EXTENSION_LEN),
			MAP_EXTENSION_LEN) != 0)
	{
		ft_printf(WRONG_EXTENSION_ERROR);
		exit(0);
	}
	get_map_size(root, map_filename);
	alloc_map(&root->map);
	import_map(&root->map, map_filename);
}

static int	is_same_width(char *line, int width, int fd)
{
	if (line && (int)ft_strlen(line) - 1 != width)
	{
		while (line)
		{
			free(line);
			line = get_next_line(fd);
		}
		free(line);
		return (FALSE);
	}
	return (TRUE);
}

static void	get_map_size(t_root *root, char *map_filename)
{
	int		count;
	int		fd;
	char	*line;

	fd = open(map_filename, O_RDONLY);
	if (fd < 1)
		close_game_at_parsing(fd, NULL, strerror(errno));
	line = get_next_line(fd);
	if (!line)
		close_game_at_parsing(fd, NULL, ALLOC_ERROR);
	root->map.width = ft_strlen(line) - 1;
	count = 0;
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
		if (!is_same_width(line, root->map.width, fd))
			close_game_at_parsing(fd, NULL, WIDTH_ERROR);
	}
	root->map.height = count;
	close(fd);
	free(line);
}

static void	alloc_map(t_tilemap *map)
{
	int	y;

	map->matrix = (t_tile **)ft_calloc(
			map->height + 1, sizeof(t_tile *));
	if (!map->matrix)
		close_game_at_parsing(0, NULL, ALLOC_ERROR);
	y = 0;
	while (y < map->height)
	{
		map->matrix[y] = (t_tile *)ft_calloc(map->width + 1, sizeof(t_tile));
		if (!map->matrix[y++])
			close_game_at_parsing(0, map, ALLOC_ERROR);
	}
}

static void	import_map(t_tilemap *map, char *map_filename)
{
	int		y;
	int		x;
	int		fd;
	char	*line;

	fd = open(map_filename, O_RDONLY);
	if (fd < 1)
		close_game_at_parsing(fd, map, strerror(errno));
	line = get_next_line(fd);
	y = 0;
	while (line)
	{
		x = -1;
		while (line[++x] != '\n')
		{
			map->matrix[y][x].c = line[x];
			map->matrix[y][x].anim = 0;
		}
		y++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}
