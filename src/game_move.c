/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:35:22 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 11:47:16 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libft.h"

static void	sl_print_moves(int moves)
{
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr_fd(moves, 1);
	ft_putstr_fd("\n", 1);
}

static void	sl_post_move(t_app *app, char t)
{
	if (t == 'E' && app->map.c_count != 0)
		ft_putendl_fd("You have not collected all the collectibles yet!", 1);
	if (t == 'E' && app->map.c_count == 0 && app->won == 0)
	{
		app->won = 1;
		ft_putendl_fd("You win!", 1);
	}
}

int	sl_game_move(t_app *app, int dx, int dy)
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
		app->map.c_count--;
	}
	app->player.x = nx;
	app->player.y = ny;
	app->moves++;
	sl_print_moves(app->moves);
	sl_post_move(app, t);
	return (sl_render_map(app));
}
