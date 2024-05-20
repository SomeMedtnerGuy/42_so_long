/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:38:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/19 18:45:41 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static long		get_delta(void);
static void		set_tiles_anims(t_root *root);
static void		update_frame(t_root *root);
static t_vector	get_screenshake_coor(int global_timer);

int	render_next_frame(t_root *root)
{
	static unsigned long	time_since_boot;

	time_since_boot += get_delta();
	if (time_since_boot > SECOND / FPS)
	{
		if (root->global_timer % FPS == 0)
			set_tiles_anims(root);
		root->global_timer++;
		update_frame(root);
		time_since_boot %= SECOND / FPS;
	}
	return (0);
}

static long	get_delta(void)
{
	static struct timespec	last_call;
	struct timespec			current_time;
	long					diff;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	diff = current_time.tv_nsec - last_call.tv_nsec;
	if (diff < 0)
		diff += SECOND;
	last_call = current_time;
	return (diff);
}

static void	set_tiles_anims(t_root *root)
{
	int	x;
	int	y;

	y = -1;
	while (++y < root->map.height)
	{
		x = -1;
		while (++x < root->map.width)
		{
			if (root->map.matrix[y][x].c == EMPTY
				|| root->map.matrix[y][x].c == COLLECTIBLE)
			{
				if (root->map.matrix[y][x].anim == TRUE)
					root->map.matrix[y][x].anim = FALSE;
				else if (rand() % 5 == 0)
					root->map.matrix[y][x].anim = TRUE;
			}
		}
	}
}

static void	update_frame(t_root *root)
{
	t_vector	world_coor;

	world_coor = get_screenshake_coor(root->global_timer);
	put_map(root);
	put_collectibles(root);
	put_player(root);
	put_rain(root);
	put_lightning(root);
	put_mov_am_baloon(root);
	mlx_put_image_to_window(root->mlx, root->win, root->world_sprite->img,
		world_coor.x, world_coor.y);
	put_mov_am(root);
}

static t_vector	get_screenshake_coor(int global_timer)
{
	t_vector	coor;

	coor.x = 0;
	coor.y = 0;
	if (global_timer % 3 == 0)
		coor.x = 1;
	if (global_timer % 4 == 0)
		coor.y = 1;
	return (coor);
}
