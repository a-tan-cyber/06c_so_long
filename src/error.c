/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 19:38:08 by amtan             #+#    #+#             */
/*   Updated: 2026/01/07 00:10:18 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <errno.h>
#include <string.h>

#include "libft.h"

int	sl_error(const char *msg)
{
	ft_putendl_fd("Error", 2);
	if (msg)
		ft_putendl_fd((char *)msg, 2);
	return (1);
}

int	sl_syserr(const char *ctx)
{
	int			err;
	const char	*msg;

	err = errno;
	msg = strerror(err);
	ft_putendl_fd("Error", 2);
	ft_putstr_fd((char *)ctx, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd((char *)msg, 2);
	return (1);
}
