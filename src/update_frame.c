/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:38:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/13 16:13:34 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	handle_player_mov(t_root *root)
{
	int	x;
	int	y;

	root->player.mov_am += 1;
	ft_printf("Moves amount: %i\n", root->player.mov_am);
	x = root->player.pos.x;
	y = root->player.pos.y;
	if (root->map.matrix[y][x] == 'C')
	{
		root->map.collectible_am -= 1;
		root->map.matrix[y][x] = '0';
	}
	else if (root->map.matrix[y][x] == 'E' && root->map.collectible_am == 0)
	{
		ft_printf("You won!\n");
		close_game(root);
	}
}

void	update_frame(t_root *root)
{
	put_map(root);
	put_collectibles(root);
	put_player(root);
	mlx_put_image_to_window(root->mlx, root->win,
		root->world_sprite->img, 0, 0);
}
