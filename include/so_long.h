/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:52:43 by amtan             #+#    #+#             */
/*   Updated: 2026/01/06 19:01:34 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

typedef struct s_app
{
	void	*mlx;
	void	*win;
}	t_app;

int		check_args(int argc, char **argv);

int		app_init(t_app *app);
void	app_cleanup(t_app *app);

#endif
