/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_basic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:42:23 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 00:55:55 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libft.h"

static int	check_not_empty(t_map *m)
{
	if (!m || !m->grid || m->h <= 0 || m->w <= 0)
		return (1);
	return (0);
}

static int	check_rectangular(t_map *m)
{
	int	y;

	y = 0;
	while (y < m->h)
	{
		if ((int)ft_strlen(m->grid[y]) != m->w)
			return (1);
		y++;
	}
	return (0);
}

static int	check_walls(t_map *m)
{
	int	x;
	int	y;

	x = 0;
	while (x < m->w)
	{
		if (m->grid[0][x] != '1')
			return (1);
		if (m->grid[m->h - 1][x] != '1')
			return (1);
		x++;
	}
	y = 0;
	while (y < m->h)
	{
		if (m->grid[y][0] != '1')
			return (1);
		if (m->grid[y][m->w - 1] != '1')
			return (1);
		y++;
	}
	return (0);
}

int	map_validate_basic(t_map *m)
{
	if (check_not_empty(m) != 0)
		return (sl_error("Map is empty"));
	if (check_rectangular(m) != 0)
		return (sl_error("Map must be rectangular"));
	if (check_walls(m) != 0)
		return (sl_error("Map must be surrounded by walls"));
	if (map_validate_charset_counts(m) != 0)
		return (1);
	return (0);
}
