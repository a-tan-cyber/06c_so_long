/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 23:54:58 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 00:19:53 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <mlx.h>

int	sl_img_new(t_app *app, t_img *img, int w, int h)
{
	if (!app || !app->mlx || !img)
		return (sl_error("Internal error: img_new"));
	img->img = mlx_new_image(app->mlx, w, h);
	if (!img->img)
		return (sl_error("mlx_new_image failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, \
&img->line_len, &img->endian);
	if (!img->addr)
		return (sl_error("mlx_get_data_addr failed"));
	img->w = w;
	img->h = h;
	return (0);
}

int	sl_img_xpm(t_app *app, t_img *img, const char *path)
{
	if (!app || !app->mlx || !img || !path)
		return (sl_error("Internal error: img_xpm"));
	img->img = mlx_xpm_file_to_image(app->mlx, (char *)path, &img->w, &img->h);
	if (!img->img)
		return (sl_error("mlx_xpm_file_to_image failed"));
	img->addr = mlx_get_data_addr(img->img, &img->bpp, \
&img->line_len, &img->endian);
	if (!img->addr)
		return (sl_error("mlx_get_data_addr failed"));
	return (0);
}

void	sl_img_destroy(t_app *app, t_img *img)
{
	if (!app || !app->mlx || !img || !img->img)
		return ;
	mlx_destroy_image(app->mlx, img->img);
	*img = (t_img){0};
}
