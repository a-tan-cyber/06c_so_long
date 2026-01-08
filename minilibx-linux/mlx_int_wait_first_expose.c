/*
** mlx_int_wait_first_expose.c for minilibx in 
** 
** Made by olivier crouzet
** Login   <ol@epita.fr>
** 
** Started on  Tue Oct 17 09:26:45 2000 olivier crouzet
** Last update Thu Jan  8 12:00:00 2026 amtan
*/



#include "mlx_int.h"

int	mlx_int_wait_first_expose(t_xvar *xvar, Window win)
{
	XEvent	ev;

	ev = (XEvent){0};
	XWindowEvent(xvar->display, win, ExposureMask, &ev);
	XPutBackEvent(xvar->display, &ev);
	return (0);
}
