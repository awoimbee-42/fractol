# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/26 22:06:19 by marvin            #+#    #+#              #
#    Updated: 2018/12/31 04:20:47 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol

CC = gcc

ECHO = @printf

CFLAGS	=	-Wall -Wextra -g3 #-Wall -Wextra -Werror

SRC_PATH =	src
OBJ_PATH =	obj

SRC_NAME =	draw_basic_mandel_julia.c	\
			draw_2.5d_mandel_julia.c	\
			draw_burningship.c			\
			draw_cos_mandel.c			\
			draw_kochsnow.c				\
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
	$(ECHO) "$(RED)Making libft...$(EOC)\n"
	make -C libft/ all

$(LIBX_FD)/libmlx.a :
	$(ECHO) "$(RED)Making libx...$(EOC)\n"
	make all -C $(LIBX_FD)


$(NAME) : $(LIBS) $(OBJ)
	$(ECHO) "$(RED)Linking $(NAME)...$(EOC)\n"
	$(CC) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(ECHO) "$(GRN)Making $@ with \"$(CFLAGS) $(CPPFLAGS)\"...$(EOC)\n"
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean :
	$(ECHO) "$(RED)Cleaning libx...$(EOC)\n"
	make clean -C $(LIBX_FD)
	$(ECHO) "$(RED)Cleaning libft...$(EOC)\n"
	make fclean -C libft
	$(ECHO) "$(RED)Cleaning objects...$(EOC)\n"
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

fclean : clean
	$(ECHO) "$(RED)Cleaning $(NAME)...$(EOC)\n"
	rm -f $(NAME)

re : fclean all

sfclean :
	$(ECHO) "$(RED)Cleaning $(NAME)...$(EOC)\n"
	rm -f $(NAME)
	$(ECHO) "$(RED)Cleaning objects...$(EOC)\n"
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true

sre: sfclean $(NAME)

RED = \033[1;31m
GRN = \033[1;32m
EOC = \033[0m