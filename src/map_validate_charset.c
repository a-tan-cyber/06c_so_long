/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_charset.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:15:24 by amtan             #+#    #+#             */
/*   Updated: 2026/01/06 19:41:17 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_allowed(char c)
{
	if (c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P')
		return (1);
	return (0);
}

static void	count_tile(t_map *m, char c)
{
	if (c == 'C')
		m->c_count++;
	else if (c == 'E')
		m->e_count++;
	else if (c == 'P')
		m->p_count++;
}

static int	scan_row(t_map *m, int y)
{
	int		x;
	char	c;

	x = 0;
	while (x < m->w)
	{
		c = m->grid[y][x];
		if (!is_allowed(c))
			return (sl_error("Map has invalid characters"));
		count_tile(m, c);
		x++;
	}
	return (0);
}

static int	check_counts(t_map *m)
{
	if (m->e_count != 1)
		return (sl_error("Map must contain exactly 1 exit (E)"));
	if (m->p_count != 1)
		return (sl_error("Map must contain exactly 1 player (P)"));
	if (m->c_count < 1)
		return (sl_error("Map must contain at least 1 collectible (C)"));
	return (0);
}

int	map_validate_charset_counts(t_map *m)
{
	int	y;

	m->c_count = 0;
	m->e_count = 0;
	m->p_count = 0;
	y = 0;
	while (y < m->h)
	{
		if (scan_row(m, y) != 0)
			return (1);
		y++;
	}
	return (check_counts(m));
}
