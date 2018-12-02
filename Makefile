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

CFLAGS	=	-Wall -Wextra #-Wall -Wextra -Werror

SRC_PATH =	src
OBJ_PATH =	obj

SRC_NAME =	main.c			\
			render.c		\
			useful_funcs.c	\
			complex_op.c	\
			mandelbrot.c	\
			save_bitmap.c
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LDFLAGS = -Llibft
LDLIBS = -lft -lmlx

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -L./minilibx_macos
	LDLIBS += -framework OpenGL -framework AppKit
	LIBX_FD = ./minilibx_macos
else
	LDFLAGS += -L./minilibx_x11
	LDLIBS += -lXext -lX11
	LIBX_FD = ./minilibx_x11
	#Don't forget you need libxext-dev & libx11-dev
endif

CPPFLAGS = -I./ -I$(LIBX_FD) -I./libft

all : $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[0;31mMaking libx...\033[0m"
	make -C $(LIBX_FD) all
	@echo "\033[0;31mMaking libft...\033[0m"
	make -C libft/ all
	@echo "\033[0;31mMaking $(NAME)...\033[0m"
	$(CC) $^ $(LDFLAGS) $(LDLIBS) -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo "\033[0;32mMaking $@ with \"$(CFLAGS) $(CPPFLAGS)\"...\033[0m"
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean :
	@echo "\033[0;31mCleaning libx...\033[0m"
	make -C $(LIBX_FD) clean
	@echo "\033[0;31mCleaning libft...\033[0m"
	make -C libft/ fclean
	@echo "\033[0;31mCleaning objects...\033[0m"
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean : clean
	@echo "\033[0;31mCleaning $(NAME)...\033[0m"
	rm -f $(NAME)

re : fclean all

sfclean :
	@echo "\033[0;31mCleaning $(NAME)...\033[0m"
	rm -f $(NAME)
	@echo "\033[0;31mCleaning objects...\033[0m"
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

sre: sfclean $(NAME)
