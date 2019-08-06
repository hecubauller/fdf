/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 21:02:35 by ubyrd             #+#    #+#             */
/*   Updated: 2019/05/25 21:15:26 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

void			ft_putwstr(wchar_t const *s)
{
	if (!s)
		return ;
	while (*s)
		ft_putwchar(*(s++));
}
