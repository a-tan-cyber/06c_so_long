/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:56:21 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 11:47:00 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <X11/keysym.h>

static int	sl_key_delta(int keycode, int *dx, int *dy)
{
	*dx = 0;
	*dy = 0;
	if (keycode == XK_w || keycode == XK_Up)
		*dy = -1;
	else if (keycode == XK_s || keycode == XK_Down)
		*dy = 1;
	else if (keycode == XK_a || keycode == XK_Left)
		*dx = -1;
	else if (keycode == XK_d || keycode == XK_Right)
		*dx = 1;
	else
		return (0);
	return (1);
}

int	sl_game_on_key(t_app *app, int keycode)
{
	int	dx;
	int	dy;

	if (!app)
		return (0);
	if (app->won != 0)
		return (0);
	if (sl_key_delta(keycode, &dx, &dy) == 0)
		return (0);
	return (sl_game_move(app, dx, dy));
}
