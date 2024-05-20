/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 20:34:26 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/20 13:26:43 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static void	create_world(t_root *root);
static void	finish_setup(t_root *root);
int			on_key_press(int keycode, t_root *root);
int			on_key_release(int keycode, t_root *root);

int	main(int argc, char **argv)
{
	t_root	root;

	if (argc != 2)
		return (ft_printf(WRONG_USAGE_ERROR), 0);
	srand(time(NULL));
	parse_map(&root, argv[1]);
	check_map_validity(&root.map);
	root.mlx = mlx_init();
	if (!root.mlx)
		return (close_game_at_parsing(0, &root.map, ALLOC_ERROR), 0);
	root.win = mlx_new_window(root.mlx,
			root.map.width * SPRITE_SIZE,
			root.map.height * SPRITE_SIZE, PROGRAM_NAME);
	if (!root.win)
		return (mlx_destroy_display(root.mlx), free(root.mlx),
			close_game_at_parsing(0, &root.map, ALLOC_ERROR), 0);
	create_world(&root);
	finish_setup(&root);
	mlx_hook(root.win, KeyPress, KeyPressMask, on_key_press, &root);
	mlx_hook(root.win, KeyRelease, KeyReleaseMask, on_key_release, &root);
	mlx_hook(root.win, DestroyNotify, 0L, close_game, &root);
	mlx_loop_hook(root.mlx, render_next_frame, &root);
	mlx_loop(root.mlx);
}

static void	create_world(t_root *root)
{
	t_sprite	*world;

	world = (t_sprite *)ft_calloc(1, sizeof(t_sprite));
	world->img = mlx_new_image(root->mlx,
			root->map.width * SPRITE_SIZE, root->map.height * SPRITE_SIZE);
	if (!world->img)
	{
		free_matrix(root->map.matrix);
		ft_printf(ALLOC_ERROR);
		exit(0);
	}
	world->addr = mlx_get_data_addr(world->img, &world->bits_per_pixel,
			&world->line_length, &world->endian);
	world->width = root->map.width * SPRITE_SIZE;
	world->height = root->map.height * SPRITE_SIZE;
	root->world_sprite = world;
}

static void	finish_setup(t_root *root)
{
	root->player.pos.x = root->map.p_start_pos.x;
	root->player.pos.y = root->map.p_start_pos.y;
	root->player.p_pos.y = root->player.pos.y;
	root->player.p_pos.x = root->player.pos.x;
	root->player.mov_am = 0;
	root->player.max_mov_am = root->map.available_space
		* (root->map.collectible_am + 1);
	root->player.mov_dir = STILL;
	root->global_timer = 0;
}

int	on_key_press(int keycode, t_root *r)
{
	if (r->player.mov_dir != STILL)
		return (0);
	if (keycode == XK_w || keycode == XK_Up)
	{
		if (r->map.matrix[r->player.pos.y - 1][r->player.pos.x].c != WALL)
			return (r->player.mov_dir = UP, handle_player_mov(r), 0);
	}
	else if (keycode == XK_s || keycode == XK_Down)
	{
		if (r->map.matrix[r->player.pos.y + 1][r->player.pos.x].c != WALL)
			return (r->player.mov_dir = DOWN, handle_player_mov(r), 0);
	}
	else if (keycode == XK_a || keycode == XK_Left)
	{
		if (r->map.matrix[r->player.pos.y][r->player.pos.x - 1].c != WALL)
			return (r->player.mov_dir = LEFT, handle_player_mov(r), 0);
	}
	else if (keycode == XK_d || keycode == XK_Right)
	{
		if (r->map.matrix[r->player.pos.y][r->player.pos.x + 1].c != WALL)
			return (r->player.mov_dir = RIGHT, handle_player_mov(r), 0);
	}
	return (0);
}

int	on_key_release(int keycode, t_root *root)
{
	if (keycode == XK_Escape)
		close_game(root);
	return (0);
}
