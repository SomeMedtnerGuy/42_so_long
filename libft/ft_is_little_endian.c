/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_little_endian.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 09:25:08 by ndo-vale          #+#    #+#             */
/*   Updated: 2024/04/18 21:32:04 by ndo-vale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_little_endian(void)
{
	int	i;

	i = 1;
	return (*(char *)&i == 1);
}
