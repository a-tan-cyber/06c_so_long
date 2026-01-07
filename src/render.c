/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:56:07 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 00:24:34 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <mlx.h>

static void	render_cell(t_app *app, int x, int y)
{
	char	t;
	t_pt	pos;
	t_img	*base;
	t_img	*spr;

	t = app->map.grid[y][x];
	pos.x = x * SL_TILE;
	pos.y = y * SL_TILE;
	base = &app->tex.floor;
	if (t == '1')
		base = &app->tex.wall;
	sl_blit_key(&app->fb, base, pos, SL_KEY);
	spr = NULL;
	if (t == 'P')
		spr = &app->tex.player;
	else if (t == 'C')
		spr = &app->tex.collect;
	else if (t == 'E')
		spr = &app->tex.exit;
	if (spr)
		sl_blit_key(&app->fb, spr, pos, SL_KEY);
}

int	sl_render_map(t_app *app)
{
	int	x;
	int	y;

	if (!app || !app->mlx || !app->win || !app->fb.img)
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
	mlx_put_image_to_window(app->mlx, app->win, app->fb.img, 0, 0);
	return (0);
}
