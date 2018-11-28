# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 22:06:19 by marvin            #+#    #+#              #
#    Updated: 2018/11/26 22:06:19 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol

CC = gcc

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIB_X_FD = ./minilibx_macos
	FRAMWRK = -framework OpenGL -framework AppKit
else
	LIB_X_FD = ./minilibx_x11
	FRAMWRK = -lXext -lX11
	#Don't forget you need libxext-dev & libx11-dev
endif

LIB	=	$(LIB_X_FD)/libmlx.a	\
		./libft/libft.a			\
		-L$(LIB_X_FD)			\
		-lm -lmlx $(FRAMWRK)

SRC	=	*.c

INCS	=	./ $(LIB_X_FD)

CFLAGS	=	-O3#-g3 -O0 #-Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(SRC) fractol.h
	make -C $(LIB_X_FD) all
	make -C libft/ all
	$(CC) $(CFLAGS) $(addprefix -I,$(INCS)) $(SRC) $(LIB) -o $(NAME)

mlx :
	make -C $(LIB_X_FD) all

libft :
	make -C libft/ all

clean :
	make -C $(LIB_X_FD) clean
	make -C libft/ clean

fclean : clean
	rm -rf $(NAME)

re : fclean all
