/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:38:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/15 15:21:30 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	update_frame(t_root *root)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (root->global_timer % 3 == 0)
		x += 1;
	if (root->global_timer % 4 == 0)
		y += 1;
	x %= 2;
	y %= 2;

	put_map(root);
	put_collectibles(root);
	put_player(root);
	put_rain(root);
	mlx_put_image_to_window(root->mlx, root->win,
		root->world_sprite->img, x, y);
}
