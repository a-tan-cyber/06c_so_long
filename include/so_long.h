/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:52:43 by amtan             #+#    #+#             */
/*   Updated: 2026/01/08 11:34:53 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stddef.h>

# define SL_KEY 0x00FF00FF

# define SL_TEX_FLOOR "textures/floor.xpm"
# define SL_TEX_WALL "textures/wall.xpm"
# define SL_TEX_PLAYER "textures/player.xpm"
# define SL_TEX_COLLECT "textures/collect.xpm"
# define SL_TEX_EXIT "textures/exit.xpm"

# define SL_TILE 32

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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_tex
{
	t_img	floor;
	t_img	wall;
	t_img	player;
	t_img	collect;
	t_img	exit;
}	t_tex;

typedef struct s_app
{
	void	*mlx;
	void	*win;
	int		win_w;
	int		win_h;
	t_img	fb;
	t_tex	tex;
	t_map	map;
	t_pt	player;
	int		moves;
	int		c_left;
	int		won;
	t_pt	exit;
}	t_app;

void			app_cleanup(t_app *app);
int				app_init(t_app *app);
int				app_run(t_app *app, const char *path);

int				check_args(int argc, char **argv);

void			map_free(t_map *m);
int				map_load(t_map *m, const char *path);

int				map_validate_basic(t_map *m);
int				map_validate_charset_counts(t_map *m);
int				map_validate_path(t_map *m);

void			sl_blit_key(t_img *dst, t_img *src, t_pt pos, unsigned int key);

int				sl_error(const char *msg);
int				sl_syserr(const char *ctx);

int				sl_game_init(t_app *app);
int				sl_game_handle_key(t_app *app, int keycode);
int				sl_game_move(t_app *app, int dx, int dy);
int				sl_game_on_key(t_app *app, int keycode);

char			**sl_grid_dup(t_map *m);
void			sl_grid_free(char **g);

int				sl_img_new(t_app *app, t_img *img, int w, int h);
int				sl_img_xpm(t_app *app, t_img *img, const char *path);
void			sl_img_destroy(t_app *app, t_img *img);

unsigned int	sl_px_get(t_img *img, int x, int y);
void			sl_px_set(t_img *img, int x, int y, unsigned int c);

int				sl_render_map(t_app *app);
int				sl_tex_load(t_app *app);
void			sl_tex_destroy(t_app *app);

#endif
