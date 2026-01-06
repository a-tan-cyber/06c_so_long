/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 21:05:58 by amtan             #+#    #+#             */
/*   Updated: 2026/01/06 17:08:39 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_app	app;

	if (!check_args(argc, argv))
		return (EXIT_FAILURE);
	if (app_init(&app) != 0)
		return (EXIT_FAILURE);
	mlx_loop(app.mlx);
	app_cleanup(&app);
	return (EXIT_SUCCESS);
}
