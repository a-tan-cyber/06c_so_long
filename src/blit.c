/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 23:57:14 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 01:26:27 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	sl_blit_key(t_img *dst, t_img *src, t_pt pos, unsigned int key)
{
	int				x;
	int				y;
	unsigned int	c;

	if (!dst || !src)
		return ;
	y = 0;
	while (y < src->h)
	{
		x = 0;
		while (x < src->w)
		{
			c = sl_px_get(src, x, y);
			if ((c & 0x00FFFFFF) != (key & 0x00FFFFFF))
				sl_px_set(dst, pos.x + x, pos.y + y, c);
			x++;
		}
		y++;
	}
}
