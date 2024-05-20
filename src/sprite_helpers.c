/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:50:18 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/20 12:40:33 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*get_sprite_path(t_root *root, t_tile tile)
{
	char	*path;

	path = NULL;
	if (tile.c == WALL)
		path = ft_strdup(WALL_PATH);
	else if (tile.c == COLLECTIBLE || tile.c == PLAYER || tile.c == EMPTY)
		path = ft_strdup(STD_EMPTY_PATH);
	else if (tile.c == EXIT)
		path = ft_strdup(EXIT_PATH);
	if (!path)
		close_game(root);
	return (path);
}

t_sprite	*create_sprite(t_root *root, char *sprite_path)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
	{
		free(sprite_path);
		close_game(root);
	}
	sprite->img = mlx_xpm_file_to_image(
			root->mlx,
			sprite_path,
			&sprite->width,
			&sprite->height);
	if (!sprite->img)
	{
		free(sprite);
		free(sprite_path);
		close_game(root);
	}
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian);
	free(sprite_path);
	return (sprite);
}

void	put_sprite_in_world(t_sprite *sprite, t_root *root, int posx, int posy)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color)
				put_pixel(root->world_sprite,
					posx * SPRITE_SIZE + x,
					posy * SPRITE_SIZE + y, color);
		}
	}
}

void	put_player_anim_in_world(t_sprite *sprite, t_root *root,
		int posx, int posy)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < sprite->height)
	{
		x = -1;
		while (++x < sprite->width)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color)
			{
				color = get_player_color(&root->player);
				put_pixel(root->world_sprite,
					posx * SPRITE_SIZE + x,
					posy * SPRITE_SIZE + y, color);
			}
		}
	}
}
