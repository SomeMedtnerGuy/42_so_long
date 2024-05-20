/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_frames.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:00:43 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/20 13:00:47 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	*get_empty_frame(t_tile tile, int timer)
{
	char	*str1;
	char	*str2;

	if (!tile.anim)
		return (ft_strdup(STD_EMPTY_PATH));
	str1 = ft_itoa(timer % FPS);
	str2 = ft_strjoin(EMPTY_PATH, str1);
	free(str1);
	str1 = ft_strjoin(str2, IMG_EXTENSION);
	free(str2);
	return (str1);
}

char	*get_player_frame(int dir)
{
	char		*str1;
	char		*str2;
	static int	i;

	if (i == 10)
	{
		i = 0;
		return (NULL);
	}
	if (dir == STILL)
		return (ft_strdup(STD_PLAYER_PATH));
	str1 = ft_itoa((dir * 10) + (i++ % FPS));
	str2 = ft_strjoin(PLAYER_PATH, str1);
	free(str1);
	str1 = ft_strjoin(str2, IMG_EXTENSION);
	free(str2);
	return (str1);
}

char	*get_collectible_frame(t_tile tile)
{
	if (!tile.anim)
		return (ft_strdup(COLLECTIBLE_PATH));
	else
		return (ft_strdup(COLLECTIBLE_PATH_HELP));
}
