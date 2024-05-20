/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_mov_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:29:06 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/19 17:16:48 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static void	handle_dir(t_root *root)
{
	if (root->player.mov_dir == UP)
	{
		root->player.p_pos.y = root->player.pos.y;
		root->player.pos.y -= 1;
	}
	else if (root->player.mov_dir == RIGHT)
	{
		root->player.p_pos.x = root->player.pos.x;
		root->player.pos.x += 1;
	}
	else if (root->player.mov_dir == DOWN)
	{
		root->player.p_pos.y = root->player.pos.y;
		root->player.pos.y += 1;
	}
	else if (root->player.mov_dir == LEFT)
	{
		root->player.p_pos.x = root->player.pos.x;
		root->player.pos.x -= 1;
	}
}

void	handle_player_mov(t_root *root)
{
	int	x;
	int	y;

	handle_dir(root);
	root->player.mov_am += 1;
	ft_printf("Moves amount: %i\n", root->player.mov_am);
	x = root->player.pos.x;
	y = root->player.pos.y;
	if (root->map.matrix[y][x].c == COLLECTIBLE)
	{
		root->map.collectible_am -= 1;
		root->map.matrix[y][x].c = EMPTY;
	}
	else if (root->map.matrix[y][x].c == EXIT && root->map.collectible_am == 0)
	{
		ft_printf(WIN_MSG);
		close_game(root);
	}
	else if (root->player.mov_am >= root->player.max_mov_am)
	{
		ft_printf(LOSE_MSG);
		close_game(root);
	}
}
