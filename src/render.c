/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:56:07 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 23:49:59 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <mlx.h>

static void	render_cell(t_app *app, int x, int y)
{
	char	t;
	void	*img;

	t = app->map.grid[y][x];
	img = app->tex.floor.img;
	if (t == '1')
		img = app->tex.wall.img;
	mlx_put_image_to_window(app->mlx, app->win, img, x * SL_TILE, y * SL_TILE);
	img = NULL;
	if (t == 'P')
		img = app->tex.player.img;
	else if (t == 'C')
		img = app->tex.collect.img;
	else if (t == 'E')
		img = app->tex.exit.img;
	if (img)
		mlx_put_image_to_window(app->mlx, app->win, img, x * SL_TILE, \
y * SL_TILE);
}

int	sl_render_map(t_app *app)
{
	int	x;
	int	y;

	if (!app || !app->mlx || !app->win)
		return (sl_error("Internal error: render"));
	y = 0;
	while (y < app->map.h)
	{
		x = 0;
		while (x < app->map.w)
		{
			render_cell(app, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
