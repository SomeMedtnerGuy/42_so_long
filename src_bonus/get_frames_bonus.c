/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_frames_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:00:43 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/05/17 08:56:33 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

char	*get_empty_frame(t_tile tile, int timer)
{
	char	*str1;
	char	*str2;

	if (!tile.anim)
		return ("./sprites_bonus/empty/empty0.xpm");
	str1 = ft_itoa(timer % FPS);
	str2 = ft_strjoin("./sprites_bonus/empty/empty", str1);
	free(str1);
	str1 = ft_strjoin(str2, ".xpm");
	free(str2);
	return (str1);
}

char    *get_player_frame(int dir, int timer)
{
        char    *str1;
        char    *str2;
	static int	i;

	(void)timer;
	if (i == 10)
	{
		dir = STILL;
		i = 0;
	}
        if (dir == STILL)
                return (STD_PLAYER_PATH);
        str1 = ft_itoa((dir * 10) + (i++ % FPS));
        str2 = ft_strjoin(PLAYER_PATH, str1);
        free(str1);
        str1 = ft_strjoin(str2, ".xpm");
        free(str2);
        return (str1);
}

char	*get_collectible_frame(t_tile tile)
{
        if (!tile.anim)
		return (ft_strdup("./sprites_bonus/collectible/collectible0.xpm"));
	else
		return (ft_strdup("./sprites_bonus/collectible/collectible1.xpm"));
}

char	*get_rain_frame(int timer)
{
	char	*str1;
	char    *str2;

        str1 = ft_itoa(timer % 4);
        str2 = ft_strjoin(RAIN_PATH, str1);
        free(str1);
        str1 = ft_strjoin(str2, ".xpm");
        free(str2);
        return (str1);

}
