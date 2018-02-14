/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:07:11 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:07:11 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "structures.h"

#include <stdio.h>

void	read_field(void);

/*
** ERRORS
*/

void	mall_error(void);
void	argnum_error(void);
void	file_error(void);
void	empty_file_error(void);

#endif
