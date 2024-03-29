/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 00:19:44 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/12 00:28:34 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

void			*ft_memalloc(size_t size)
{
	void			*a;

	a = malloc(size);
	return (a ? ft_memset(a, 0, size) : NULL);
}
