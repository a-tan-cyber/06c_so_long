/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:52:43 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 14:00:44 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stddef.h>

enum e_map_err
{
	MAP_OK = 0,
	MAP_ERR_OPEN = 1,
	MAP_ERR_EMPTY = 2,
	MAP_ERR_READ = 3
};

typedef struct s_map
{
	char	**grid;
	int		w;
	int		h;
	int		c_count;
	int		e_count;
	int		p_count;
}	t_map;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	t_map	map;
}	t_app;

typedef struct s_pt
{
	int	x;
	int	y;
}	t_pt;

typedef struct s_reach
{
	int	c;
	int	e;
}	t_reach;

typedef struct s_flood
{
	char	**g;
	t_map	*m;
	t_pt	*st;
	size_t	cap;
	size_t	top;
	t_reach	reach;
}	t_flood;

void	app_cleanup(t_app *app);
int		app_init(t_app *app);
int		app_run(t_app *app, const char *path);

int		check_args(int argc, char **argv);

void	map_free(t_map *m);
int		map_load(t_map *m, const char *path);

int		map_validate_basic(t_map *m);
int		map_validate_charset_counts(t_map *m);
int		map_validate_path(t_map *m);

int		sl_error(const char *msg);
int		sl_syserr(const char *ctx);

char	**sl_grid_dup(t_map *m);
void	sl_grid_free(char **g);

#endif
