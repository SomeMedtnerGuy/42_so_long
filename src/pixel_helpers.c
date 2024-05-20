/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/20 13:56:12 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_pixel(t_sprite *sprite, int x, int y, int color)
{
	char	*dst;

	dst = sprite->addr + (y * sprite->line_length
			+ x * (sprite->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_color_in_pixel(t_sprite *sprite, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(sprite->addr
			+ (y * sprite->line_length
				+ x * (sprite->bits_per_pixel / 8)));
	return (color);
}

int	get_player_color(t_entity *player)
{
	int	moves_spent_perc;
	int	color;

	color = 0;
	moves_spent_perc = (player->mov_am * 100) / player->max_mov_am;
	if (moves_spent_perc < 50)
		color = (moves_spent_perc * 2 * MAX_COLOR) / 100 << (BITE_SIZE * 2)
			| MAX_COLOR << BITE_SIZE | 0;
	else
		color = MAX_COLOR << (BITE_SIZE * 2)
			| (MAX_COLOR - (((moves_spent_perc - 50) * 2 * MAX_COLOR)
					/ 100)) << BITE_SIZE | 0;
	return (color);
}
