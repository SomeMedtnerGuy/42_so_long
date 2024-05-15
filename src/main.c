/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:34:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/13 16:14:01 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

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
	if (keycode == XK_w || keycode == XK_Up)
	{
		if (root->map.matrix[root->player.pos.y - 1][root->player.pos.x] != '1')
			return (root->player.pos.y -= 1, handle_player_mov(root), 0);
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		if (root->map.matrix[root->player.pos.y + 1][root->player.pos.x] != '1')
			return (root->player.pos.y += 1, handle_player_mov(root), 0);
	}
	else if (keycode == XK_a || keycode == XK_Left)
	{
		if (root->map.matrix[root->player.pos.y][root->player.pos.x - 1] != '1')
			return (root->player.pos.x -= 1, handle_player_mov(root), 0);
	}
	else if (keycode == XK_d || keycode == XK_Right)
	{
		if (root->map.matrix[root->player.pos.y][root->player.pos.x + 1] != '1')
			return (root->player.pos.x += 1, handle_player_mov(root), 0);
	}
	return (0);
}

int	render_next_frame(t_root *root)
{
	static unsigned int	call_no;

	if (call_no++ % (120000 / FPS) == 0)
	{
		root->global_timer++;
		update_frame(root);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_root	root;

	if (argc != 2)
		return (0);
	parse_map(&root, argv[1]);
	is_map_valid(&root.map);
	root.mlx = mlx_init();
	root.win = mlx_new_window(root.mlx,
			root.map.width * SPRITE_SIZE,
			root.map.height * SPRITE_SIZE, "so_long");
	create_world(&root);
	root.player.pos.x = root.map.p_start_pos.x;
	root.player.pos.y = root.map.p_start_pos.y;
	root.player.mov_am = 0;
	mlx_hook(root.win, KeyPress, KeyPressMask, on_key_press, &root);
	mlx_hook(root.win, KeyRelease, KeyReleaseMask, on_key_release, &root);
	mlx_hook(root.win, DestroyNotify, 0L, close_game, &root);
	mlx_loop_hook(root.mlx, render_next_frame, &root);
	mlx_loop(root.mlx);
}
