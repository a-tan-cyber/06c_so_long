/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 17:55:18 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 00:23:19 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	destroy_one(t_app *app, t_img *img)
{
	sl_img_destroy(app, img);
}

static int	load_one(t_app *app, t_img *img, const char *path)
{
	if (sl_img_xpm(app, img, path) != 0)
		return (1);
	return (0);
}

void	sl_tex_destroy(t_app *app)
{
	if (!app)
		return ;
	destroy_one(app, &app->tex.exit);
	destroy_one(app, &app->tex.collect);
	destroy_one(app, &app->tex.player);
	destroy_one(app, &app->tex.wall);
	destroy_one(app, &app->tex.floor);
}

int	sl_tex_load(t_app *app)
{
	if (!app || !app->mlx)
		return (sl_error("Internal error: tex_load"));
	if (load_one(app, &app->tex.floor, SL_TEX_FLOOR) != 0)
		return (sl_tex_destroy(app), sl_error("Failed to load floor.xpm"));
	if (load_one(app, &app->tex.wall, SL_TEX_WALL) != 0)
		return (sl_tex_destroy(app), sl_error("Failed to load wall.xpm"));
	if (load_one(app, &app->tex.player, SL_TEX_PLAYER) != 0)
		return (sl_tex_destroy(app), sl_error("Failed to load player.xpm"));
	if (load_one(app, &app->tex.collect, SL_TEX_COLLECT) != 0)
		return (sl_tex_destroy(app), sl_error("Failed to load collect.xpm"));
	if (load_one(app, &app->tex.exit, SL_TEX_EXIT) != 0)
		return (sl_tex_destroy(app), sl_error("Failed to load exit.xpm"));
	return (0);
}
