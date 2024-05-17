/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:34:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/17 19:03:25 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	create_world(t_root *root)
{
	t_sprite	*world;

	world = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	world->img = mlx_new_image(root->mlx,
			root->map.width * SPRITE_SIZE, root->map.height * SPRITE_SIZE);
	if (!world->img)
	{
		ft_printf(ALLOC_ERROR);
		return ;
	}
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
	world->width = root->map.width * SPRITE_SIZE;
	world->height = root->map.height * SPRITE_SIZE;
	root->world_sprite = world;
}

int	on_key_release(int keycode, t_root *root)
{
	if (keycode == XK_Escape)
		close_game(root);
	return (0);
}

int	on_key_press(int keycode, t_root *root)
{
	if (root->player.mov_dir != STILL)
		return (0);
	if (keycode == XK_w || keycode == XK_Up)
	{
		if (root->map.matrix[root->player.pos.y - 1][root->player.pos.x].c != '1')
			return (root->player.mov_dir = UP, handle_player_mov(root), 0);
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		if (root->map.matrix[root->player.pos.y + 1][root->player.pos.x].c != '1')
			return (root->player.mov_dir = DOWN, handle_player_mov(root), 0);
	}
	else if (keycode == XK_a || keycode == XK_Left)
	{
		if (root->map.matrix[root->player.pos.y][root->player.pos.x - 1].c != '1')
			return (root->player.mov_dir = LEFT, handle_player_mov(root), 0);
	}
	else if (keycode == XK_d || keycode == XK_Right)
	{
		if (root->map.matrix[root->player.pos.y][root->player.pos.x + 1].c != '1')
			return (root->player.mov_dir = RIGHT, handle_player_mov(root), 0);
	}
	return (0);
}

void	set_tiles_anims(t_root *root)
{
	int	x;
	int	y;

	y = -1;
	while (++y < root->map.height)
	{
		x = -1;
		while (++x < root->map.width)
		{
			if (root->map.matrix[y][x].c == '0'
				|| root->map.matrix[y][x].c == 'C')
			{
				if (root->map.matrix[y][x].anim == 1)
					root->map.matrix[y][x].anim = 0;
				else if (rand() % 5 == 0)
					root->map.matrix[y][x].anim = 1;
			}
		}
	}
}

long	get_delta(void)
{
	static struct timespec	last_call;
	struct timespec	current_time;
	long	diff;

	clock_gettime(CLOCK_MONOTONIC, &current_time);
	diff = current_time.tv_nsec - last_call.tv_nsec;
	if (diff < 0)
		diff += SECOND;
	last_call = current_time;
	return (diff);
}

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

void	finish_setup(t_root *root)
{
	root->player.pos.x = root->map.p_start_pos.x;
        root->player.pos.y = root->map.p_start_pos.y;
	root->player.p_pos.y = root->player.pos.y;
	root->player.p_pos.x = root->player.pos.x;
        root->player.mov_am = 0;
	root->player.max_mov_am = root->map.available_space * (root->map.collectible_am + 1);
	root->player.mov_dir = STILL;
	root->global_timer = 0;
}

int	main(int argc, char **argv)
{
	t_root	root;

	if (argc != 2)
		return (0);
	srand(time(NULL));
	parse_map(&root, argv[1]);
	is_map_valid(&root.map);
	root.mlx = mlx_init();
	root.win = mlx_new_window(root.mlx,
			root.map.width * SPRITE_SIZE,
			root.map.height * SPRITE_SIZE, "so_long");
	create_world(&root);
	finish_setup(&root);
	mlx_hook(root.win, KeyPress, KeyPressMask, on_key_press, &root);
	mlx_hook(root.win, KeyRelease, KeyReleaseMask, on_key_release, &root);
	mlx_hook(root.win, DestroyNotify, 0L, close_game, &root);
	mlx_loop_hook(root.mlx, render_next_frame, &root);
	mlx_loop(root.mlx);
}
