/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 23:32:47 by ubyrd             #+#    #+#             */
/*   Updated: 2019/05/25 23:34:31 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

size_t			ft_wstrlen(const wchar_t *s)
{
	size_t			i;

	i = 0;
	while (*s)
		i += ft_wcharlen(*(s++));
	return (i);
}
