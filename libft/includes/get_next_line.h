/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/21 12:27:58 by ubyrd             #+#    #+#             */
/*   Updated: 2019/05/21 13:47:42 by ubyrd            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft_basic.h"

/*
** Buffer size
*/
# define BUFF_SIZE 256

/*
** GNL return and other values
*/
# define GNL_OK 1
# define GNL_END 0
# define GNL_ERR -1

# define READ_ERR -1
# define NO_EOL -1
# define NO_PARAM 0

/*
** linefunc() function parameters
*/
# define LINE_ADD 1
# define LINE_CPY 2
# define LINE_ZERO 3
# define LINE_EOL 4

/*
** lstroot() function parameters
*/
# define FREE_ROOT 0
# define GET_ROOT 1

/*
** gnl_lstdel() function parameters
*/
# define FREE_ALL 0
# define FREE_ELEM 1

/*
** File buffer struct
*/
typedef struct	s_buf
{
	int				fd;
	char			buf[BUFF_SIZE + 1];
}				t_buf;

/*
** Usable function
*/
int				gnl_buffree(const int func_param, const int fd);
int				get_next_line(const int fd, char **line);

#endif
