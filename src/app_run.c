/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:43:47 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 02:07:38 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <mlx.h>

int	app_run(t_app *app, const char *path)
{
	if (map_load(&app->map, path) != 0)
		return (1);
	if (map_validate_basic(&app->map) != 0)
		return (1);
	if (map_validate_path(&app->map) != 0)
		return (1);
	if (app_init(app) != 0)
		return (1);
	if (sl_tex_load(app) != 0)
		return (1);
	if (sl_game_init(app) != 0)
		return (1);
	if (sl_render_map(app) != 0)
		return (1);
	mlx_loop(app->mlx);
	return (0);
}
