/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 01:37:01 by ubyrd             #+#    #+#             */
/*   Updated: 2019/04/18 16:45:28 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_basic.h"

char			*ft_strtrim(char const *s)
{
	char			*a;
	size_t			i;

	if (!s)
		return (NULL);
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	i = ft_strlen(s);
	while (i && (*(s + i - 1) == ' '
		|| *(s + i - 1) == '\n' || *(s + i - 1) == '\t'))
		i--;
	if (!(a = (char *)malloc(i + 1)))
		return (NULL);
	*(a + i) = '\0';
	while (i-- != 0)
		*(a + i) = *(s + i);
	return (a);
}
