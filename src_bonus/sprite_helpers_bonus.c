/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helpers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:50:18 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/15 15:20:56 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

char	*get_sprite_path(t_tile tile, int timer)
{
	if (tile.c == '1')
		return (WALL_PATH);
	else if (tile.c == 'C' || tile.c == 'P' || tile.c == '0')
		return (get_empty_frame(tile, timer));
	else if (tile.c == 'E')
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
	//free(sprite_path);
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

void	put_player_anim_in_world(t_sprite *sprite, t_root *root, int posx, int posy)
{
        int                             x;
        int                             y;
        unsigned int    color;

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

void    put_rain_anim_in_world(t_sprite *sprite, t_root *root, int posx, int posy)
{
        int                             x;
        int                             y;
        unsigned int    color;

        y = -1;
        while (++y < root->world_sprite->height)
        {
                x = -1;
                while (++x < root->world_sprite->width)
                {
                        color = get_color_in_pixel(sprite, x, y);
                        if (color)
                                put_pixel(root->world_sprite,
                                        posx * SPRITE_SIZE + x,
                                        posy * SPRITE_SIZE + y, color);
                }
        }
}

