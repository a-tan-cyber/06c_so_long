/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:52:43 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 00:11:36 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

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

int		sl_error(const char *msg);
int		sl_syserr(const char *ctx);

int		check_args(int argc, char **argv);

int		map_load(t_map *m, const char *path);
void	map_free(t_map *m);

int		map_validate_basic(t_map *m);
int		map_validate_charset_counts(t_map *m);

int		app_init(t_app *app);
void	app_cleanup(t_app *app);

#endif
