/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_player_mov_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:29:06 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/17 11:17:16 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static void     handle_up(t_root *root)
{
        root->player.p_pos.y = root->player.pos.y;
        root->player.pos.y -= 1;
}

static void	handle_right(t_root *root)
{
	root->player.p_pos.x = root->player.pos.x;
	root->player.pos.x += 1;
}

static void	handle_down(t_root *root)
{
	root->player.p_pos.y = root->player.pos.y;
        root->player.pos.y += 1;
}

static void     handle_left(t_root *root)
{
        root->player.p_pos.x = root->player.pos.x;
        root->player.pos.x -= 1;
}

void	handle_player_mov(t_root *root)
{
	int	x;
	int	y;

	if (root->player.mov_dir == UP)
		handle_up(root);
	else if (root->player.mov_dir == RIGHT)
		handle_right(root);
	else if (root->player.mov_dir == DOWN)
		handle_down(root);
	else if (root->player.mov_dir == LEFT)
		handle_left(root);
	root->player.mov_am += 1;
	ft_printf("Moves amount: %i\n", root->player.mov_am);
	x = root->player.pos.x;
	y = root->player.pos.y;
	if (root->map.matrix[y][x].c == 'C')
	{
		root->map.collectible_am -= 1;
		root->map.matrix[y][x].c = '0';
	}
	else if (root->map.matrix[y][x].c == 'E' && root->map.collectible_am == 0)
	{
		ft_printf("You won!\n");
		close_game(root);
	}
	else if (root->player.mov_am >= root->player.max_mov_am)
	{
		ft_printf("You ran out of stamina! You lost!!");
		close_game(root);
	}
}
