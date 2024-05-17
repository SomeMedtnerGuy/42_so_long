/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_helpers_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:50:18 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/17 21:47:47 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

char	*get_sprite_path(t_tile tile, int timer)
{
	if (tile.c == '1')
		return (ft_strdup(WALL_PATH));
	else if (tile.c == 'C' || tile.c == 'P' || tile.c == '0')
		return (get_empty_frame(tile, timer));
	else if (tile.c == 'E')
		return (ft_strdup(EXIT_PATH));
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

int	get_player_color(t_entity *player)
{
	int	moves_spent_perc;
	int	color;

	color = 0;
	moves_spent_perc = (player->mov_am * 100) / player->max_mov_am;
	if (moves_spent_perc < 50)
		color = (moves_spent_perc * 2 * 0xFF) / 100 << 16 | 0xFF << 8 | 0;
	else
		color = 0xFF << 16 | (0xFF - (((moves_spent_perc - 50) * 2 * 0xFF) / 100)) << 8 | 0;
	return (color);
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
			{
				color = get_player_color(&root->player);
                                put_pixel(root->world_sprite,
                                        posx * SPRITE_SIZE + x,
                                        posy * SPRITE_SIZE + y, color);
			}
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

