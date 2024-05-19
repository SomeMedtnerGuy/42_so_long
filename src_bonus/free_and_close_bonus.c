/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_close_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:44:24 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/19 09:47:19 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	close_game_at_parsing(int fd, t_tilemap *map, char *error_msg)
{
	if (fd)
		close(fd);
	if (map)
		free_matrix(map->matrix);
	ft_printf("%s", error_msg);
	exit(0);
}

int	close_game(t_root *root)
{
	free_matrix(root->map.matrix);
	mlx_destroy_image(root->mlx, root->world_sprite->img);
	free(root->world_sprite);
	mlx_destroy_window(root->mlx, root->win);
	mlx_destroy_display(root->mlx);
	free(root->mlx);
	exit(0);
	return (0);
}

void	free_matrix(t_tile **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}
