/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 01:56:21 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 02:06:51 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdlib.h>
#include <X11/keysym.h>

#include "libft.h"

static void	print_moves(int moves)
{
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(moves, 1);
	ft_putchar_fd('\n', 1);
}

static void	win_and_exit(t_app *app)
{
	app_cleanup(app);
	exit(EXIT_SUCCESS);
}

static int	try_move(t_app *app, int dx, int dy)
{
	int		nx;
	int		ny;
	char	t;

	nx = app->player.x + dx;
	ny = app->player.y + dy;
	if (nx < 0 || ny < 0 || nx >= app->map.w || ny >= app->map.h)
		return (0);
	t = app->map.grid[ny][nx];
	if (t == '1')
		return (0);
	if (t == 'C')
	{
		app->map.grid[ny][nx] = '0';
		app->c_left--;
	}
	app->player.x = nx;
	app->player.y = ny;
	app->moves++;
	print_moves(app->moves);
	sl_render_map(app);
	if (t == 'E' && app->c_left == 0)
		win_and_exit(app);
	return (1);
}

int	sl_game_init(t_app *app)
{
	int	x;
	int	y;

	if (!app)
		return (sl_error("Internal error: game_init"));
	app->moves = 0;
	app->c_left = app->map.c_count;
	y = 0;
	while (y < app->map.h)
	{
		x = 0;
		while (x < app->map.w)
		{
			if (app->map.grid[y][x] == 'P')
			{
				app->player.x = x;
				app->player.y = y;
				app->map.grid[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
	return (sl_error("Map has no player"));
}

int	sl_game_handle_key(t_app *app, int keycode)
{
	if (!app)
		return (0);
	if (keycode == XK_w || keycode == XK_Up)
		return (try_move(app, 0, -1));
	if (keycode == XK_s || keycode == XK_Down)
		return (try_move(app, 0, 1));
	if (keycode == XK_a || keycode == XK_Left)
		return (try_move(app, -1, 0));
	if (keycode == XK_d || keycode == XK_Right)
		return (try_move(app, 1, 0));
	return (0);
}
