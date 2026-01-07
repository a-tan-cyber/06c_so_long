/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:56:07 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 02:07:24 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <mlx.h>

static void	render_cell(t_app *app, int x, int y)
{
	char	t;
	t_pt	p;

	t = app->map.grid[y][x];
	p.x = x * SL_TILE;
	p.y = y * SL_TILE;
	sl_blit_key(&app->fb, &app->tex.floor, p, SL_KEY);
	if (t == '1')
		sl_blit_key(&app->fb, &app->tex.wall, p, SL_KEY);
	else if (t == 'C')
		sl_blit_key(&app->fb, &app->tex.collect, p, SL_KEY);
	else if (t == 'E')
		sl_blit_key(&app->fb, &app->tex.exit, p, SL_KEY);
}

int	sl_render_map(t_app *app)
{
	int		x;
	int		y;
	t_pt	p;

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
	p.x = app->player.x * SL_TILE;
	p.y = app->player.y * SL_TILE;
	sl_blit_key(&app->fb, &app->tex.player, p, SL_KEY);
	mlx_put_image_to_window(app->mlx, app->win, app->fb.img, 0, 0);
	return (0);
}
