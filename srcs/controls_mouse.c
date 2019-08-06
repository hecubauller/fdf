/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 11:42:57 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 13:40:00 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				mouse_press(int button, int x, int y, void *param)
{
	t_fdf			*f;

	f = (t_fdf *)param;
	if (y < 0)
		return (0);
	else if (button == 4 || button == 5)
		f->scale += button == 4 ? M_SCL_DIFF : -M_SCL_DIFF;
	else if (button == 1 || button == 2)
		f->flags |= button == 1 ? F_LBUT : F_RBUT;
	else if (button == 3)
		f->flags |= F_MBUT;
	else
		return (0);
	if (button == 4 || button == 5)
	{
		f->scale < 0 ? f->scale = 0 : 0;
		draw_multithreading(f);
	}
	else
	{
		f->mouse_x = x;
		f->mouse_y = y;
	}
	return (1);
}

int				mouse_release(int button, int x, int y, void *param)
{
	t_fdf			*f;

	(void)button;
	(void)x;
	(void)y;
	f = (t_fdf *)param;
	if (button == 1)
		f->flags &= ~F_LBUT;
	else if (button == 2)
		f->flags &= ~F_RBUT;
	else if (button == 3)
		f->flags &= ~F_MBUT;
	return (0);
}

int				mouse_move(int x, int y, void *param)
{
	t_fdf			*f;

	f = (t_fdf *)param;
	if (f->flags & F_LBUT)
	{
		f->bet += (x - f->mouse_x) * M_ANG_DIFF;
		f->alp += (f->mouse_y - y) * M_ANG_DIFF;
	}
	else if (f->flags & F_RBUT)
	{
		f->x_off += (x - f->mouse_x) * M_OFF_DIFF;
		f->y_off += (y - f->mouse_y) * M_OFF_DIFF;
	}
	else if (f->flags & F_MBUT)
		f->gam += (x - f->mouse_x) * M_ANG_DIFF;
	else
		return (0);
	draw_multithreading(f);
	f->mouse_x = x;
	f->mouse_y = y;
	return (1);
}
