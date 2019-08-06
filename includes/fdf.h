/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <ubyrd@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 21:11:15 by ubyrd             #+#    #+#             */
/*   Updated: 2019/06/15 14:36:47 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <limits.h>
# include <pthread.h>

/*
** ---------- FLAGS ----------
*/

# define F_LBUT (1u << 7u)
# define F_MBUT (1u << 6u)
# define F_RBUT (1u << 5u)
# define F_HELP (1u << 4u)
# define F_ISO  (1u << 3u)
# define F_PAR1 (1u << 2u)
# define F_PAR2 (1u << 1u)
# define F_PAR3 (1u << 0u)

/*
** ---------- MACROS ----------
*/

# define ABS(a)      ((a) > 0 ? (a) : -(a))
# define MAX(a, b)   ((a) > (b) ? (a) : (b))
# define MIN(a, b)   ((a) < (b) ? (a) : (b))

# define WIN_TITLE   "FDF"
# define WIN_W       1920
# define WIN_H       1200

# define MAX_SIDE    (WIN_W / 2)
# define MAX_HEIGHT  (WIN_W / 10)

# define ANG_DIFF    0.025
# define OFF_DIFF    6
# define SCL_DIFF    0.1
# define MULT_DIFF   0.0125

# define M_ANG_DIFF  0.005
# define M_OFF_DIFF  1
# define M_SCL_DIFF  0.1

# define N_THREADS   8

# define ISO_SIN     0.50000019433
# define ISO_COS     0.86602529158

/*
** ---------- COLORS ----------
*/

# define BG_COL      0x333333
# define TEXT_COL    0xEEEEEE

# define COL_SET_N 3
# define HGRD_COL(a) HGRD_COL ## a
# define ZGRD_COL(a) ZGRD_COL ## a
# define LGRD_COL(a) LGRD_COL ## a

# define HGRD_COL1   0xFF0000
# define ZGRD_COL1   0x00BB44
# define LGRD_COL1   0x0000FF

# define HGRD_COL2   0xFF856B
# define ZGRD_COL2   0x581845
# define LGRD_COL2   0xA284D3

# define HGRD_COL3   0x88FF44
# define ZGRD_COL3   0x000000
# define LGRD_COL3   0xFFFFFF

/*
** ---------- STRUCTURES ----------
*/

typedef struct	s_point
{
	int				x;
	int				y;
	int				z;
	int				c;
	char			c_flag;
}				t_point;

typedef struct	s_fdf
{
	void			*mp;
	void			*wp;
	unsigned short	flags;

	t_point			**m;
	int				m_i;
	int				m_i_max;
	int				m_j;
	int				m_j_max;
	int				pix_off;
	int				z_min;
	int				z_max;

	void			*ip;
	int				*idata_c;
	int				*idata_z;

	int				x_off;
	int				y_off;
	float			z_mult;
	float			scale;
	double			alp;
	double			bet;
	double			gam;

	int				colorset;
	int				hgrd_col;
	int				zgrd_col;
	int				lgrd_col;

	int				mouse_x;
	int				mouse_y;
}				t_fdf;

typedef struct	s_fdf_t_arg
{
	t_fdf			*f;
	int				cur_i_start;
	int				cur_i_end;
}				t_fdf_t_arg;

/*
** ---------- FUNCTIONS ----------
*/

/*
** utils.c
*/
int				init(t_fdf *f);
void			destroy(t_fdf *f, char *message);
char			*check_num(char *s, int n);
void			strhexlowcase(char *s);
void			set_colorset(t_fdf *f);

/*
** utils2.c
*/
void			set_color(t_fdf *f);
int				get_color(t_point a, t_point b, int coord, char c_coord);
void			print_help(t_fdf *f);

/*
** reader.c
*/
int				reader(t_fdf *f, char *filename);

/*
** project.c
*/
t_point			project(t_fdf *f, t_point a);

/*
** draw.c
*/
void			*draw(void *arg);

/*
** draw_multithreading.c
*/
void			draw_multithreading(t_fdf *f);

/*
** controls_keyboard.c
*/
int				key_press(int keycode, void *param);
int				close_win(void *param);

/*
** controls_mouse.c
*/
int				mouse_press(int button, int x, int y, void *param);
int				mouse_release(int button, int x, int y, void *param);
int				mouse_move(int x, int y, void *param);

#endif
