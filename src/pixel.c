/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 23:55:46 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 23:55:51 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

unsigned int	sl_px_get(t_img *img, int x, int y)
{
	char	*px;

	if (!img || !img->addr || x < 0 || y < 0 || x >= img->w || y >= img->h)
		return (0);
	px = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	return (*(unsigned int *)px);
}

void	sl_px_set(t_img *img, int x, int y, unsigned int c)
{
	char	*px;

	if (!img || !img->addr || x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	px = img->addr + (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)px = c;
}
