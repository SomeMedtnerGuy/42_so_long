/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_effects_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 18:59:11 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/19 19:16:16 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	put_rain(t_root *root)
{
	t_sprite	*sprite;

	sprite = create_sprite(root, get_rain_frame(root->global_timer));
	put_rain_anim_in_world(sprite, root, 0, 0);
	mlx_destroy_image(root->mlx, sprite->img);
	free(sprite);
}

void	put_lightning(t_root *root)
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

void	put_mov_am_baloon(t_root *root)
{
	t_sprite	*sprite;

	if (root->player.mov_dir == STILL)
	{
		sprite = create_sprite(root, ft_strdup(BALOON_PATH));
		put_sprite_in_world(sprite, root,
			root->player.pos.x, root->player.pos.y - 1);
		mlx_destroy_image(root->mlx, sprite->img);
		free(sprite);
	}
}

void	put_mov_am(t_root *root)
{
	char	*mov_am_str;
	int		x_offset;

	if (root->player.mov_dir == STILL)
	{
		mov_am_str = ft_itoa(root->player.mov_am);
		if (root->player.mov_am < 10)
			x_offset = 2;
		else if (root->player.mov_am < 100)
			x_offset = 5;
		else
			x_offset = 8;
		mlx_string_put(root->mlx, root->win,
			root->player.pos.x * SPRITE_SIZE + SPRITE_SIZE / 2 - x_offset,
			root->player.pos.y * SPRITE_SIZE - SPRITE_SIZE / 4,
			WHITE, mov_am_str);
		free(mov_am_str);
	}
}
