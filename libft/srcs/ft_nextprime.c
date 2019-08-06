/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nextprime.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 01:56:23 by ubyrd             #+#    #+#             */
/*   Updated: 2019/05/13 03:33:23 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

int				ft_nextprime(int n)
{
	int				x;

	if (n <= 1)
		return (2);
	x = 3;
	n = n % 2 ? n + 2 : n + 1;
	if (n < 0)
		return (0);
	while ((n / x) >= x)
	{
		if (!(n % x))
		{
			n += 2;
			x = 3;
			continue ;
		}
		x += 2;
	}
	return (n);
}
