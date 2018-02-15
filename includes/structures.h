/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkolosov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 13:07:18 by nkolosov          #+#    #+#             */
/*   Updated: 2018/02/13 13:07:18 by nkolosov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

#include <string.h>

typedef enum
{
	FREE = 0, MY = 1, ENEMY
}				t_owner;

typedef struct	s_cell
{
	size_t	closest;
	size_t	valid;
	t_owner	initial;
}				t_cell;

typedef struct	s_field
{
	t_cell		**cells;
	size_t		width;
	size_t		height;
}				t_field;

typedef struct	s_piece_cell
{
	_Bool	init;
	_Bool	val;
}				t_piece_cell;

typedef struct	s_piece
{
	t_piece_cell	**cells;
	size_t			init_width;
	size_t			init_height;
	size_t			width;
	size_t			height;
	size_t			delta_w;
	size_t			delta_h;

}				t_piece;

#endif
