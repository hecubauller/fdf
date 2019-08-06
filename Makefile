# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ubyrd <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/21 00:32:42 by ubyrd             #+#    #+#              #
#    Updated: 2019/06/14 15:22:46 by ubyrd            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GRN			=	\x1B[32m
MAG			=	\x1B[35m
RES			=	\x1B[0m


NAME			=	fdf

# FDF
SRC_PATH		=	srcs/
OBJ_PATH		=	srcs/obj/
INC_PATH		=	includes/
# LIBFT
LIB_PATH		=	libft/
LIB_INC_PATH	=	libft/includes/

# FDF
SRC_NAME		=	main.c utils.c utils2.c reader.c project.c \
					draw.c draw_multithreading.c controls_keyboard.c \
					controls_mouse.c
OBJ_NAME		=	$(SRC_NAME:.c=.o)
INC_NAME		=	fdf.h
# LIBFT
LIB_NAME		=	libft.a
LIB_INC_NAME	=	libft.h

# FDF
OBJ				=	$(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC				=	$(addprefix $(INC_PATH), $(INC_NAME))
# LIBFT
LIB				=	$(addprefix $(LIB_PATH), $(LIB_NAME))
LIB_INC			=	$(addprefix $(LIB_INC_PATH), $(LIB_INC_NAME))

.PHONY:				all $(LIB_NAME) clean fclean re


all:				$(LIB_NAME) $(NAME)

# LIBFT
$(LIB_NAME):
					@make -C $(LIB_PATH)
# FDF
$(NAME):			$(LIB) $(OBJ)
					@gcc -Wall -Wextra -Werror $(OBJ) \
						-lmlx -framework OpenGL -framework AppKit -lm \
						-L $(LIB_PATH) -lft -o $(NAME)
					@echo "$(GRN)\nLinking [ $(NAME) ] SUCCESS$(RES)"

# LIBFT
$(LIB):				$(LIB_NAME)
# FDF
$(OBJ_PATH)%.o:		$(SRC_PATH)%.c $(INC) $(LIB_INC)
					@mkdir -p $(OBJ_PATH)
					@gcc -Wall -Wextra -Wextra \
						-I $(INC_PATH) -I $(LIB_INC_PATH) -o $@ -c $<
					@echo "$(GRN).\c$(RES)"

clean:
					@make -C $(LIB_PATH) fclean
					@rm -f $(OBJ)
					@rm -rf $(OBJ_PATH)
					@echo "$(MAG)Cleaning [ $(NAME) ] OK$(RES)"

fclean:				clean
					@rm -f $(NAME)
					@echo "$(MAG)Delete [ $(NAME) ] OK$(RES)"

re:					fclean all
