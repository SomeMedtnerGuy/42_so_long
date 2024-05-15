/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:34:14 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/13 20:58:08 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static int	get_map_size(t_root *root, char *map_filename);
static void	import_map(t_tilemap *map, char *map_filename);
static int	is_same_width(char *line, int width, int fd);
static void	alloc_map(t_root *root);

void	parse_map(t_root *root, char *map_filename)
{
	if (ft_strncmp(".ber", map_filename
			+ (ft_strlen(map_filename) - 4), 4) != 0)
	{
		ft_printf(WRONG_EXTENTION_ERROR);
		exit(0);
	}
	get_map_size(root, map_filename);
	alloc_map(root);
	import_map(&root->map, map_filename);
}

static void	import_map(t_tilemap *map, char *map_filename)
{
	int		y;
	int		x;
	int		fd;
	char	*line;

	fd = open(map_filename, O_RDONLY);
	if (fd < 1)
		free_map_and_exit(map);
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

static void	alloc_map(t_root *root)
{
	int	y;

	root->map.matrix = (t_tile **)ft_calloc(root->map.height + 1, sizeof(t_tile *));
	if (!root->map.matrix)
	{
		ft_printf(ALLOC_ERROR);
		exit(0);
	}
	y = 0;
	while (y < root->map.height)
	{
		root->map.matrix[y] = (t_tile *)ft_calloc(
				root->map.width + 1, sizeof(t_tile));
		if (!root->map.matrix[y++])
		{
			free_matrix(root->map.matrix);
			ft_printf(ALLOC_ERROR);
			exit (0);
		}
	}
}

static int	get_map_size(t_root *root, char *map_filename)
{
	int		count;
	int		fd;
	char	*line;

	fd = open(map_filename, O_RDONLY);
	if (fd < 1)
		return (perror(NULL), exit(0), -1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), ft_printf(ALLOC_ERROR), exit(0), -1);
	root->map.width = ft_strlen(line) - 1;
	count = 0;
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
		if (!is_same_width(line, root->map.width, fd))
			return (close(fd), ft_printf(WIDTH_ERROR, count + 1),
				exit(0), -1);
	}
	root->map.height = count;
	close(fd);
	free(line);
	return (count);
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
