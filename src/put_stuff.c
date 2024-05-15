/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:46:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/13 14:46:41 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	put_map(t_root *root)
{
	int			y;
	int			x;
	t_sprite	*sprite;

	y = -1;
	while (++y < root->map.height)
	{
		x = -1;
		while (++x < root->map.width)
		{
			sprite = create_sprite(root,
					get_sprite_path(
						root->map.matrix[y][x]));
			put_sprite_in_world(sprite, root, x, y);
			mlx_destroy_image(root->mlx, sprite->img);
			free(sprite);
		}
	}
}

void	put_player(t_root *root)
{
	root->player.sprite = create_sprite(root, PLAYER_PATH);
	put_sprite_in_world(root->player.sprite, root,
		root->player.pos.x, root->player.pos.y);
	mlx_destroy_image(root->mlx, root->player.sprite->img);
	free(root->player.sprite);
}

void	put_collectibles(t_root *root)
{
	t_sprite	*sprite;
	int			x;
	int			y;

	y = -1;
	while (++y < root->map.height)
	{
		x = -1;
		while (++x < root->map.width)
		{
			if (root->map.matrix[y][x] == 'C')
			{
				sprite = create_sprite(root, COLLECTIBLE_PATH);
				put_sprite_in_world(sprite, root, x, y);
				mlx_destroy_image(root->mlx, sprite->img);
				free(sprite);
			}
		}
	}
}
