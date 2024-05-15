/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:50:18 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/10 17:45:15 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*get_sprite_path(char component)
{
	if (component == '1')
		return (WALL_PATH);
	else if (component == '0' || component == 'C' || component == 'P')
		return (EMPTY_PATH);
	else if (component == 'E')
		return (EXIT_PATH);
	return (NULL);
}

t_sprite	*create_sprite(t_root *root, char *sprite_path)
{
	t_sprite	*sprite;

	sprite = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	sprite->img = mlx_xpm_file_to_image(
			root->mlx,
			sprite_path,
			&sprite->width,
			&sprite->height);
	sprite->addr = mlx_get_data_addr(sprite->img, &sprite->bits_per_pixel,
			&sprite->line_length, &sprite->endian);
	return (sprite);
}

void	put_sprite_in_world(t_sprite *sprite, t_root *root, int posx, int posy)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < SPRITE_SIZE)
	{
		x = -1;
		while (++x < SPRITE_SIZE)
		{
			color = get_color_in_pixel(sprite, x, y);
			if (color)
				put_pixel(root->world_sprite,
					posx * SPRITE_SIZE + x,
					posy * SPRITE_SIZE + y, color);
		}
	}
}
