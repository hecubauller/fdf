/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 18:38:13 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 09:24:36 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		free_tab(char **tab)
{
	int				i;

	i = -1;
	while (tab[++i])
		free((void *)tab[i]);
	free((void *)tab);
}

static int		create_matrix(t_fdf *f, char *filename)
{
	int				fd;
	int				st;
	int				i;
	char			*line;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (0);
	i = 0;
	while ((st = get_next_line(fd, &line)) > 0)
	{
		i++;
		free((void *)line);
	}
	line ? free((void *)line) : 0;
	f->m_i_max = i;
	if (!(f->m = (t_point **)ft_memalloc(sizeof(t_point *) * (f->m_i_max + 1))))
		return (0);
	if (close(fd) == -1)
		return (0);
	return (st ? 0 : 1);
}

static int		get_z_c(t_fdf *f, char *str)
{
	char			*num;

	f->m[f->m_i][f->m_j].z = ft_atoi(str);
	f->m[f->m_i][f->m_j].z > f->z_max ? f->z_max = f->m[f->m_i][f->m_j].z : 0;
	f->m[f->m_i][f->m_j].z < f->z_min ? f->z_min = f->m[f->m_i][f->m_j].z : 0;
	if (!(str = check_num(str, f->m[f->m_i][f->m_j].z)))
		return (0);
	if (*str == ',' && ft_strlen(str) == 9)
	{
		f->m[f->m_i][f->m_j].c = ft_atoi_base(str++ + 3, 16);
		if (!(num = ft_itoa_base(f->m[f->m_i][f->m_j].c, 16)))
			return (0);
		if (!ft_strncmp("0x", str, 2))
			strhexlowcase(num);
		else
			ft_strncmp("0X", str, 2) ? f->m_i = -1 : 0;
		str += 2;
		while (*str && *str == '0' && *(str + 1))
			str++;
		ft_strncmp(num, str, ft_strlen(num)) ? f->m_i = -1 : 0;
		str += ft_strlen(num);
		free((void *)num);
	}
	return (*str || f->m_i == -1 ? 0 : 1);
}

static int		add_points(t_fdf *f, char **tab)
{
	f->m_j = -1;
	while (tab[++f->m_j])
		;
	!f->m_i ? f->m_j_max = f->m_j : 0;
	!f->m_i ? f->pix_off =
		MAX(MAX_SIDE / MAX((MAX(f->m_i_max, f->m_j_max) - 1), 1), 1) : 0;
	if (!(f->m[f->m_i] = (t_point *)malloc(sizeof(t_point) * f->m_j_max)))
		return (0);
	f->m_j = -1;
	while (tab[++f->m_j])
	{
		f->m[f->m_i][f->m_j].x = f->pix_off * (f->m_j - f->m_j_max / 2) +
			((!(f->m_j_max % 2) || f->m_i_max == 1) && f->m_j_max != 1 ?
			f->pix_off / 2 : 0);
		f->m[f->m_i][f->m_j].y = f->pix_off * (f->m_i - f->m_i_max / 2) +
			((!(f->m_i_max % 2) || f->m_i_max == 1) && f->m_i_max != 1 ?
			f->pix_off / 2 : 0);
		f->m[f->m_i][f->m_j].c = -1;
		if (!get_z_c(f, tab[f->m_j]))
			break ;
		f->m[f->m_i][f->m_j].c_flag = f->m[f->m_i][f->m_j].c == -1 ? 1 : 0;
	}
	f->m_i++;
	return (tab[f->m_j] || f->m_j != f->m_j_max ? 0 : 1);
}

int				reader(t_fdf *f, char *filename)
{
	int				fd;
	int				st;
	char			*line;
	char			**tab;

	if (!create_matrix(f, filename) || (fd = open(filename, O_RDONLY)) == -1)
		return (0);
	while ((st = get_next_line(fd, &line)) > 0)
	{
		if (!(tab = ft_strsplit(line, ' ')))
		{
			free((void *)line);
			return (0);
		}
		if (!(add_points(f, tab)))
		{
			free_tab(tab);
			free((void *)line);
			return (0);
		}
		free_tab(tab);
		free((void *)line);
	}
	line ? free((void *)line) : 0;
	return (st || !*f->m ? 0 : 1);
}
