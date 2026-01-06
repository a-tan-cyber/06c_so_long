/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 00:21:25 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 00:21:29 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdlib.h>

void	map_free(t_map *m)
{
	int	i;

	if (!m)
		return ;
	if (m->grid)
	{
		i = 0;
		while (m->grid[i])
		{
			free(m->grid[i]);
			i++;
		}
		free(m->grid);
	}
	*m = (t_map){0};
}
