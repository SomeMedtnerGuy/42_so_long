/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_next_frame.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 16:38:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/19 18:45:41 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static long		get_delta(void);
static void		update_frame(t_root *root);

int	render_next_frame(t_root *root)
{
	static unsigned long	time_since_boot;

	time_since_boot += get_delta();
	if (time_since_boot > SECOND / FPS)
	{
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

static void	update_frame(t_root *root)
{
	put_map(root);
	put_collectibles(root);
	put_player(root);
	mlx_put_image_to_window(root->mlx, root->win, root->world_sprite->img,
		0, 0);
}
