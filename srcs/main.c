/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 03:30:22 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 12:12:45 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				main(int argc, char **argv)
{
	t_fdf			f;

	if (argc != 2)
	{
		ft_putstr("Usage: fdf input_file\n");
		return (0);
	}
	ft_bzero((void *)&f, sizeof(t_fdf));
	if (!reader(&f, argv[1]) || !init(&f))
		destroy(&f, "Error\n");
	draw_multithreading(&f);
	mlx_hook(f.wp, 2, 0, &key_press, (void *)&f);
	mlx_hook(f.wp, 4, 0, &mouse_press, (void *)&f);
	mlx_hook(f.wp, 5, 0, &mouse_release, (void *)&f);
	mlx_hook(f.wp, 6, 0, &mouse_move, (void *)&f);
	mlx_hook(f.wp, 17, 0, &close_win, (void *)&f);
	mlx_loop(f.mp);
	destroy(&f, "Error\n");
	return (0);
}
