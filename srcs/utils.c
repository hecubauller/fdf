/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 01:46:31 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 08:48:52 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				init(t_fdf *f)
{
	char			*idata;
	int				garbage[3];

	if (!(f->mp = mlx_init()))
		return (0);
	if (!(f->wp = mlx_new_window(f->mp, WIN_W, WIN_H, WIN_TITLE)))
		return (0);
	if (!(f->ip = mlx_new_image(f->mp, WIN_W, WIN_H)))
		return (0);
	if (!(idata = mlx_get_data_addr(f->ip, garbage, garbage + 1, garbage + 2)))
		return (0);
	f->idata_c = (int *)idata;
	if (!(f->idata_z = (int *)malloc(sizeof(int) * WIN_W * WIN_H)))
		return (0);
	f->z_mult = (float)MAX_HEIGHT / MAX(f->z_max - f->z_min, 1);
	f->scale = 1;
	set_colorset(f);
	f->flags |= F_ISO;
	f->flags |= F_HELP;
	return (1);
}

void			destroy(t_fdf *f, char *message)
{
	int				i;

	gnl_buffree(FREE_ALL, NO_PARAM);
	if (f->m)
	{
		i = -1;
		while (f->m[++i])
			free((void *)(f->m[i]));
		free((void *)f->m);
	}
	f->idata_z ? free((void *)f->idata_z) : 0;
	f->ip ? mlx_destroy_image(f->mp, f->ip) : 0;
	f->wp ? mlx_destroy_window(f->mp, f->wp) : 0;
	message ? write(1, message, ft_strlen(message)) : 0;
	exit(0);
}

char			*check_num(char *s, int n)
{
	int				i;
	char			*num;

	i = (*s == '-' || *s == '+') ? 0 : -1;
	while (s[++i] == '0')
		;
	if (!(num = ft_itoa(n)) ||
		(*s == '-' && ft_strncmp(num + 1, s + i, ft_strlen(num) - 1)) ||
		(*s != '-' && ft_strncmp(num, s + (n ? i : i - 1), ft_strlen(num))) ||
		(*s == '-' && !n))
	{
		num ? free((void *)num) : 0;
		return (NULL);
	}
	s += (n ? ft_strlen(num) : 0) + i - (*s == '-' ? 1 : 0);
	free((void *)num);
	return (s);
}

void			strhexlowcase(char *s)
{
	while (*s)
	{
		if (*s >= 'A' && *s <= 'F')
			*s += 32;
		s++;
	}
}

void			set_colorset(t_fdf *f)
{
	f->colorset = !f->colorset || f->colorset >= COL_SET_N ?
		1 : f->colorset + 1;
	if (f->colorset == 1)
	{
		f->hgrd_col = HGRD_COL(1);
		f->lgrd_col = LGRD_COL(1);
		f->zgrd_col = ZGRD_COL(1);
	}
	else if (f->colorset == 2)
	{
		f->hgrd_col = HGRD_COL(2);
		f->lgrd_col = LGRD_COL(2);
		f->zgrd_col = ZGRD_COL(2);
	}
	else if (f->colorset == 3)
	{
		f->hgrd_col = HGRD_COL(3);
		f->lgrd_col = LGRD_COL(3);
		f->zgrd_col = ZGRD_COL(3);
	}
	set_color(f);
}
