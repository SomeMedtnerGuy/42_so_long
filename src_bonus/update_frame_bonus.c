/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:38:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/17 21:55:01 by ndo-vale         ###   ########.fr       */
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
	put_lightning(root);
	if (root->player.mov_dir == STILL)
	{
		t_sprite	*spritee = create_sprite(root, ft_strdup("./sprites_bonus/baloon.xpm"));
		put_sprite_in_world(spritee, root, root->player.pos.x, root->player.pos.y - 1);
		mlx_destroy_image(root->mlx, spritee->img);
		free(spritee);
	}
	mlx_put_image_to_window(root->mlx, root->win,
		root->world_sprite->img, x, y);
	char *mov_am_str = ft_itoa(root->player.mov_am);
	int	x_offset;
	if (root->player.mov_am < 10)
		x_offset = 2;
	else if (root->player.mov_am < 100)
		x_offset = 5;
	else
		x_offset = 8;
	if (root->player.mov_dir == STILL)
		mlx_string_put(root->mlx, root->win,
			root->player.pos.x * SPRITE_SIZE + SPRITE_SIZE/2 - x_offset,
			root->player.pos.y * SPRITE_SIZE - SPRITE_SIZE/4,
			0xFFFFFF, mov_am_str);
	free(mov_am_str);
}
