/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amtan <amtan@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 17:07:30 by amtan             #+#    #+#             */
/*   Updated: 2026/01/06 17:07:46 by amtan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include "libft.h"

static int	is_ber_file(const char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (len < 4)
		return (0);
	if (ft_strncmp(path + len - 4, ".ber", 4) != 0)
		return (0);
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Usage: ./so_long <map.ber>", 2);
		return (0);
	}
	if (!is_ber_file(argv[1]))
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Map must have .ber extension", 2);
		return (0);
	}
	return (1);
}
