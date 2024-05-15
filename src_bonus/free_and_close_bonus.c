/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_close_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:44:24 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/13 19:27:39 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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

void	free_map_and_exit(t_tilemap *map)
{
	free_matrix(map->matrix);
	perror(NULL);
	exit (0);
}
