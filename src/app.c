/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:08:16 by amtan             #+#    #+#             */
/*   Updated: 2026/01/06 17:08:17 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <mlx.h>
#include <stdlib.h>
#include <X11/keysym.h>
#include <X11/X.h>

#include "libft.h"

void	app_cleanup(t_app *app)
{
	if (app->win)
	{
		mlx_destroy_window(app->mlx, app->win);
		app->win = NULL;
	}
	if (app->mlx)
	{
		mlx_destroy_display(app->mlx);
		free(app->mlx);
		app->mlx = NULL;
	}
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
	app->win = NULL;
	if (!app->mlx)
	{
		ft_putendl_fd("mlx_init failed", 2);
		return (1);
	}
	app->win = mlx_new_window(app->mlx, 640, 480, "so_long smoke test");
	if (!app->win)
	{
		ft_putendl_fd("mlx_new_window failed", 2);
		app_cleanup(app);
		return (1);
	}
	mlx_hook(app->win, KeyPress, KeyPressMask, on_keydown, app);
	mlx_hook(app->win, DestroyNotify, 0, on_destroy, app);
	return (0);
}
