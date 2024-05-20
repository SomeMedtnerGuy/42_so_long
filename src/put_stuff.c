/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:46:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/20 12:57:40 by ndo-vale         ###   ########.fr       */
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
					get_sprite_path(root,
						root->map.matrix[y][x]));
			put_sprite_in_world(sprite, root, x, y);
			mlx_destroy_image(root->mlx, sprite->img);
			free(sprite);
		}
	}
}

void	put_player(t_root *root)
{
	t_vector	drawing_pos;
	char		*player_frame;

	player_frame = NULL;
	if (!player_frame)
	{
		root->player.mov_dir = STILL;
		root->player.p_pos = root->player.pos;
		player_frame = ft_strdup(STD_PLAYER_PATH);
	}
	else if (root->player.mov_dir == STILL
		&& root->map.matrix[root->player.pos.y][root->player.pos.x].c == EXIT)
		player_frame = ft_strdup(PLAYER_STANDING_PATH);
	root->player.sprite = create_sprite(root, player_frame);
	if (root->player.mov_dir == STILL || root->player.mov_dir == LEFT
		|| root->player.mov_dir == UP)
		drawing_pos = root->player.pos;
	else
		drawing_pos = root->player.p_pos;
	put_player_anim_in_world(root->player.sprite, root,
		drawing_pos.x, drawing_pos.y);
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
			if (root->map.matrix[y][x].c == COLLECTIBLE)
			{
				sprite = create_sprite(root,
						get_collectible_frame(
							root->map.matrix[y][x]));
				put_sprite_in_world(sprite, root, x, y);
				mlx_destroy_image(root->mlx, sprite->img);
				free(sprite);
			}
		}
	}
}
