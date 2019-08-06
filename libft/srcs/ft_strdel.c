/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 00:38:52 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/15 20:56:13 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

void			ft_strdel(char **as)
{
	if (!as || !*as)
		return ;
	free((void *)(*as));
	*as = NULL;
}
