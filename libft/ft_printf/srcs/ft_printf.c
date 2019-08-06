/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 11:20:34 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/01 02:25:02 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				ft_printf(const char *format, ...)
{
	t_printf		p;
	t_printf		*p_ptr;

	p_ptr = &p;
	p.buff_i = 0;
	p.out_len = 0;
	p.fd = 1;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
			parse_format(p_ptr);
		else if (*p.format == '{' && color_check(p_ptr))
			color_print(p_ptr);
		else
			buffer(p_ptr, p.format, 1);
		p.format++;
	}
	va_end(p.ap);
	write(p.fd, p.buff, p.buff_i);
	return (p.out_len += p.buff_i);
}

int				ft_dprintf(int fd, const char *format, ...)
{
	t_printf		p;
	t_printf		*p_ptr;

	p_ptr = &p;
	p.buff_i = 0;
	p.out_len = 0;
	p.fd = fd;
	p.format = (char *)format;
	va_start(p.ap, format);
	while (*p.format)
	{
		if (*p.format == '%')
			parse_format(p_ptr);
		else if (*p.format == '{' && color_check(p_ptr))
			color_print(p_ptr);
		else
			buffer(p_ptr, p.format, 1);
		p.format++;
	}
	va_end(p.ap);
	write(p.fd, p.buff, p.buff_i);
	return (p.out_len += p.buff_i);
}

void			buffer(t_printf *p, char *src, int size)
{
	while (BUFF_SIZE - p->buff_i < size)
	{
		size -= BUFF_SIZE - p->buff_i;
		while (p->buff_i < BUFF_SIZE)
			p->buff[p->buff_i++] = *(src++);
		write(p->fd, p->buff, BUFF_SIZE);
		p->out_len += p->buff_i;
		p->buff_i = 0;
	}
	while (size--)
		p->buff[p->buff_i++] = *(src++);
}

void			padding(t_printf *p, int func_param)
{
	int				padding;

	padding = p->padding;
	if (func_param == 0)
		while (padding--)
			buffer(p, "0", 1);
	else if (func_param == 1)
		while (padding--)
			buffer(p, " ", 1);
}
