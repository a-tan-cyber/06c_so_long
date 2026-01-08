/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:43:47 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 11:54:32 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <mlx.h>

#include "libft.h"

static void	sl_print_hello(void)
{
	ft_putendl_fd("Hello there! Use W, A, S, D or the arrow keys to move.", 1);
	ft_putendl_fd("Collect all the collectibles and reach the exit to win!", 1);
}

static int	sl_find_char(t_map *m, char ch, t_pt *out)
{
	int	x;
	int	y;

	if (!m || !m->grid || !out)
		return (1);
	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (m->grid[y][x] == ch)
			{
				out->x = x;
				out->y = y;
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	sl_prepare_game(t_app *app, const char *path)
{
	app->moves = 0;
	app->won = 0;
	app->player.x = 0;
	app->player.y = 0;
	app->exit.x = 0;
	app->exit.y = 0;
	if (map_load(&app->map, path) != 0)
		return (1);
	if (map_validate_basic(&app->map) != 0)
		return (1);
	if (map_validate_path(&app->map) != 0)
		return (1);
	if (sl_find_char(&app->map, 'P', &app->player) != 0)
		return (sl_error("Internal error: missing player"));
	if (sl_find_char(&app->map, 'E', &app->exit) != 0)
		return (sl_error("Internal error: missing exit"));
	app->map.grid[app->player.y][app->player.x] = '0';
	return (0);
}

int	app_run(t_app *app, const char *path)
{
	if (sl_prepare_game(app, path) != 0)
		return (1);
	if (app_init(app) != 0)
		return (1);
	if (sl_tex_load(app) != 0)
		return (1);
	if (sl_render_map(app) != 0)
		return (1);
	sl_print_hello();
	mlx_loop(app->mlx);
	return (0);
}
