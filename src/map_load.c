/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_load.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:42:08 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 00:24:28 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

static void	strip_eol(char *s)
{
	size_t	len;

	if (!s)
		return ;
	len = ft_strlen(s);
	while (len > 0 && (s[len - 1] == '\n' || s[len - 1] == '\r'))
	{
		len--;
		s[len] = '\0';
	}
}

static int	map_load_fail(t_map *m, int ret, int errsv)
{
	if (m)
		map_free(m);
	if (ret == MAP_ERR_OPEN)
	{
		errno = errsv;
		return (sl_syserr("open"));
	}
	if (ret == MAP_ERR_EMPTY)
		return (sl_error("Map is empty"));
	return (sl_error("Failed to read map"));
}

static int	measure_map(const char *path, int *h, int *w, int *errsv)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		*errsv = errno;
		return (MAP_ERR_OPEN);
	}
	*h = 0;
	*w = 0;
	line = get_next_line(fd);
	while (line)
	{
		strip_eol(line);
		if (*h == 0)
			*w = (int)ft_strlen(line);
		(*h)++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (*h == 0 || *w == 0)
		return (MAP_ERR_EMPTY);
	return (MAP_OK);
}

static int	fill_grid(const char *path, t_map *m, int *errsv)
{
	int		fd;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		*errsv = errno;
		return (MAP_ERR_OPEN);
	}
	i = 0;
	while (i < m->h)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		strip_eol(line);
		m->grid[i] = line;
		i++;
	}
	m->grid[i] = NULL;
	close(fd);
	if (i != m->h)
		return (MAP_ERR_READ);
	return (MAP_OK);
}

int	map_load(t_map *m, const char *path)
{
	int	ret;
	int	errsv;

	if (!m || !path)
		return (sl_error("Internal error: map_load args"));
	map_free(m);
	errsv = 0;
	ret = measure_map(path, &m->h, &m->w, &errsv);
	if (ret != MAP_OK)
		return (map_load_fail(NULL, ret, errsv));
	m->grid = (char **)ft_calloc((size_t)m->h + 1, sizeof(char *));
	if (!m->grid)
		return (sl_error("Out of memory"));
	ret = fill_grid(path, m, &errsv);
	if (ret != MAP_OK)
		return (map_load_fail(m, ret, errsv));
	return (0);
}
