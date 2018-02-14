/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:27:34 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:27:34 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libft.h"

void	mall_error(void)
{
	ft_printf("Error: Malloc fail!\n");
	exit (1);
}

void	nan_error(void)
{
	ft_printf("Error: File contains invalid characters!\n");
	exit (1);
}

void	argnum_error(void)
{
	ft_printf("Usage: ./fdf filename");
	exit (0);
}

void	file_error(void)
{
	ft_printf("%s\n", strerror(errno));
	exit (0);
}

void	empty_file_error(void)
{
	ft_printf("Error: The file is empty!");
	exit (1);
}

void	elem_num_error(void)
{
	ft_printf("Error: Wrong number of elements per line!");
	exit (1);
}
