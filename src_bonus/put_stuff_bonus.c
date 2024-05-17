/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_stuff_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:46:53 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/17 11:15:59 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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
						root->map.matrix[y][x],
						root->global_timer));
			put_sprite_in_world(sprite, root, x, y);
			mlx_destroy_image(root->mlx, sprite->img);
			free(sprite);
		}
	}
}

void	put_player(t_root *root)
{
	t_vector	drawing_pos;
	char	*player_frame;

	player_frame = get_player_frame(root->player.mov_dir, root->global_timer);
	if (ft_strncmp(player_frame, STD_PLAYER_PATH, ft_strlen(STD_PLAYER_PATH)) == 0)
	{
		root->player.mov_dir = STILL;
                root->player.p_pos = root->player.pos;
	}
	root->player.sprite = create_sprite(root, player_frame);
	if (root->player.mov_dir == STILL || root->player.mov_dir == LEFT || root->player.mov_dir == UP)
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
			if (root->map.matrix[y][x].c == 'C')
			{
				sprite = create_sprite(root, 
					get_collectible_frame(root->map.matrix[y][x]));
				put_sprite_in_world(sprite, root, x, y);
				mlx_destroy_image(root->mlx, sprite->img);
				free(sprite);
			}
		}
	}
}

void	put_rain(t_root *root)
{
	t_sprite	*sprite;

	sprite = create_sprite(root, get_rain_frame(root->global_timer));
	put_rain_anim_in_world(sprite, root, 0, 0);
	mlx_destroy_image(root->mlx, sprite->img);
        free(sprite);
}

void	put_lightning	(t_root *root)
{
	int	x;
	int	y;

	if (root->global_timer % 100 != 0
		&& (root->global_timer + 3) % 100 != 0
		&& (root->global_timer + 4) % 100 != 0)
		return ;
	y = -1;
	while (++y < root->world_sprite->height)
	{
		x = -1;
		while (++x < root->world_sprite->width)
			add_brightness_to_pixel(root->world_sprite, x, y);
	}
}
