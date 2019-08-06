# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 00:32:42 by ubyrd             #+#    #+#              #
#    Updated: 2019/06/14 15:18:45 by ubyrd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN			=	\x1B[32m
MAG			=	\x1B[35m
RES			=	\x1B[0m


NAME			=	libftprintf.a

SRC_PATH		=	srcs/
OBJ_PATH		=	obj/
INC_PATH		=	includes/
LIB_INC_PATH	=	../includes/

SRC_NAME		=	ft_printf.c parsing.c int.c int_caster.c float.c \
					float_handler.c float_utils.c float_prec.c float_writer.c \
					char.c colors.c miscellaneous.c
OBJ_NAME		=	$(SRC_NAME:.c=.o)
INC_NAME		=	ft_printf.h
LIB_INC_NAME	=	libft.h libft_basic.h get_next_line.h

SRC				=	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ				=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC				=	$(addprefix $(INC_PATH), $(INC_NAME))
LIB_INC			=	$(addprefix $(LIB_INC_PATH), $(LIB_INC_NAME))

.PHONY:				all clean fclean re


all:				$(NAME)

$(NAME):			$(OBJ)
					@ar rc $(NAME) $(OBJ)
					@echo "$(GRN)\nLinking [ $(NAME) ] SUCCESS$(RES)"

$(LIB):				$(LIB_NAME)

$(OBJ_PATH)%.o:		$(SRC_PATH)%.c $(INC) $(LIB_INC)
					@mkdir -p $(OBJ_PATH)
					@gcc -Wall -Wextra -Wextra \
						-I $(INC_PATH) -I $(LIB_INC_PATH) -o $@ -c $<
					@echo "$(GRN).\c$(RES)"

clean:
					@rm -f $(OBJ)
					@rm -rf $(OBJ_PATH)
					@echo "$(MAG)Cleaning [ $(NAME) ] OK$(RES)"

fclean:				clean
					@rm -f $(NAME)
					@echo "$(MAG)Delete [ $(NAME) ] OK$(RES)"

re:					fclean all
