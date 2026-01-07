/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:08:16 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 13:44:33 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <mlx.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>

void	app_cleanup(t_app *app)
{
	if (!app)
		return ;
	map_free(&app->map);
	if (app->mlx && app->win)
		mlx_destroy_window(app->mlx, app->win);
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
	}
	*app = (t_app){0};
}

static int	on_destroy(void *param)
{
	t_app	*app;

	app = (t_app *)param;
	app_cleanup(app);
	exit(EXIT_SUCCESS);
	return (0);
}

static int	on_keydown(int keycode, void *param)
{
	if (keycode == XK_Escape)
		return (on_destroy(param));
	return (0);
}

int	app_init(t_app *app)
{
	app->mlx = mlx_init();
	if (!app->mlx)
		return (sl_error("mlx_init failed"));
	app->win = mlx_new_window(app->mlx, 640, 480, "so_long");
	if (!app->win)
		return (sl_error("mlx_new_window failed"));
	mlx_hook(app->win, KeyPress, KeyPressMask, on_keydown, app);
	mlx_hook(app->win, DestroyNotify, 0, on_destroy, app);
	return (0);
}
