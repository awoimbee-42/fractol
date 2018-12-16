# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 22:06:19 by marvin            #+#    #+#              #
#    Updated: 2018/12/16 21:20:16 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol

CC = gcc

CFLAGS	=	-Wall -Wextra #-Wall -Wextra -Werror

SRC_PATH =	src
OBJ_PATH =	obj

SRC_NAME =	draw_slow_mandel_julia.c	\
			draw_mandel_julia.c			\
			draw_burningship.c			\
			draw_cos_mandel.c			\
			export_bmp.c				\
			main.c						\
			mlx_hooks.c					\
			render.c					\
			render_threading.c			\
			useful_funcs.c				\
			complex_op.c				\
			complex_op1.c				\
			complex_op2.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LDLIBS = -lft -lmlx -lm -lpthread

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBX_FD = ./minilibx_macos
	LDLIBS += -framework OpenGL -framework AppKit
else
	LIBX_FD = ./minilibx_x11
	LDLIBS += -lXext -lX11
	#Don't forget you need libxext-dev & libx11-dev
endif

LDFLAGS = -Llibft -L$(LIBX_FD)

CPPFLAGS = -I./ -I$(LIBX_FD) -I./libft

LIBS = libft/libft.a $(LIBX_FD)/libmlx.a

all : $(NAME)

libft/libft.a :
	@echo -e "\033[0;31mMaking libft...\033[0m"
	make -C libft/ all

$(LIBX_FD)/libmlx.a :
	@echo -e "\e[0;31mMaking libx...\033[0m"
	make all -C $(LIBX_FD)


$(NAME) : $(LIBS) $(OBJ)
	@echo -e "\033[0;31mLinking $(NAME)...\033[0m"
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@echo -e "\033[0;32mMaking $@ with \"$(CFLAGS) $(CPPFLAGS)\"...\033[0m"
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean :
	@echo -e "\033[0;31mCleaning libx...\033[0m"
	make clean -C $(LIBX_FD)
	@echo -e "\033[0;31mCleaning libft...\033[0m"
	make fclean -C libft
	@echo -e "\033[0;31mCleaning objects...\033[0m"
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean : clean
	@echo -e "\033[0;31mCleaning $(NAME)...\033[0m"
	rm -f $(NAME)

re : fclean all

sfclean :
	@echo -e "\033[0;31mCleaning $(NAME)...\033[0m"
	rm -f $(NAME)
	@echo -e "\033[0;31mCleaning objects...\033[0m"
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

sre: sfclean $(NAME)
