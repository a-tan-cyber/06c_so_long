/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:30:28 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 13:30:30 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdlib.h>

#include "libft.h"

void	sl_grid_free(char **g)
{
	int	i;

	if (!g)
		return ;
	i = 0;
	while (g[i])
	{
		free(g[i]);
		i++;
	}
	free(g);
}

char	**sl_grid_dup(t_map *m)
{
	char	**g;
	int		y;

	g = (char **)malloc(sizeof(char *) * ((size_t)m->h + 1));
	if (!g)
		return (NULL);
	y = 0;
	while (y < m->h)
	{
		g[y] = ft_strdup(m->grid[y]);
		if (!g[y])
		{
			g[y] = NULL;
			sl_grid_free(g);
			return (NULL);
		}
		y++;
	}
	g[y] = NULL;
	return (g);
}
