/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 21:29:30 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/17 21:29:52 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

int				ft_sqrt(int n)
{
	long			x;

	if (n <= 0)
		return (0);
	x = 1;
	while ((x * x) < n)
		x++;
	if ((n % x) == 0)
		return (x);
	else
		return (0);
}
