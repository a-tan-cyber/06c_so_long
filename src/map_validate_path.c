/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validate_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:05:53 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 14:01:05 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdint.h>
#include <stdlib.h>

static int	find_player(t_map *m, t_pt *p)
{
	int	x;
	int	y;

	y = 0;
	while (y < m->h)
	{
		x = 0;
		while (x < m->w)
		{
			if (m->grid[y][x] == 'P')
			{
				p->x = x;
				p->y = y;
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

static int	push_cell(t_flood *f, int x, int y)
{
	char	t;

	if (x < 0 || y < 0 || x >= f->m->w || y >= f->m->h)
		return (0);
	t = f->g[y][x];
	if (t == '1' || t == 'V')
		return (0);
	if (t == 'C')
		f->reach.c++;
	if (t == 'E')
		f->reach.e = 1;
	f->g[y][x] = 'V';
	if (f->top >= f->cap)
		return (1);
	f->st[f->top].x = x;
	f->st[f->top].y = y;
	f->top++;
	return (0);
}

static int	flood_step(t_flood *f, t_pt cur)
{
	if (push_cell(f, cur.x + 1, cur.y) != 0)
		return (1);
	if (push_cell(f, cur.x - 1, cur.y) != 0)
		return (1);
	if (push_cell(f, cur.x, cur.y + 1) != 0)
		return (1);
	if (push_cell(f, cur.x, cur.y - 1) != 0)
		return (1);
	return (0);
}

static int	flood_iter(t_flood *f, t_pt start)
{
	int		err;
	t_pt	cur;

	f->st = (t_pt *)malloc(sizeof(t_pt) * f->cap);
	if (!f->st)
		return (1);
	f->top = 0;
	f->reach = (t_reach){0};
	err = push_cell(f, start.x, start.y);
	while (err == 0 && f->top > 0)
	{
		f->top--;
		cur = f->st[f->top];
		err = flood_step(f, cur);
	}
	free(f->st);
	f->st = NULL;
	return (err);
}

int	map_validate_path(t_map *m)
{
	t_flood	f;
	t_pt	start;
	int		ret;

	f = (t_flood){0};
	if (!m || m->w <= 0 || m->h <= 0)
		return (sl_error("Map is empty"));
	if ((size_t)m->w > SIZE_MAX / (size_t)m->h)
		return (sl_error("Map too large"));
	if (find_player(m, &start) != 0)
		return (sl_error("Missing player position"));
	f.m = m;
	f.cap = (size_t)m->w * (size_t)m->h;
	f.g = sl_grid_dup(m);
	if (!f.g)
		return (sl_error("Out of memory"));
	ret = flood_iter(&f, start);
	sl_grid_free(f.g);
	if (ret != 0)
		return (sl_error("Out of memory"));
	if (f.reach.c != m->c_count || f.reach.e == 0)
		return (sl_error("No valid path"));
	return (0);
}
