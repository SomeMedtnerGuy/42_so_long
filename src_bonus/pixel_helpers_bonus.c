/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_helpers_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:51:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/16 09:58:39 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

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

static void	add_brightness_to_color(unsigned char *color, unsigned char brightness)
{
	int	i;

	i = (int)(*color);
	i += (int)brightness;
	if (i > 255)
	{
		i = 255;
	}
	*color = (unsigned char)i;
}

void	add_brightness_to_pixel(t_sprite *sprite, int x, int y)
{
	char	*dst;
	int	i;

	dst = sprite->addr + (y * sprite->line_length
                        + x * (sprite->bits_per_pixel / 8));
	i = 0;
	while (i++ < 4)
	{
		add_brightness_to_color((unsigned char *)dst, 127);
		dst++;
	}
}
