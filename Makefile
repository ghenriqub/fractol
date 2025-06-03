# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghenriqu <ghenriqu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 13:40:54 by ghenriqu          #+#    #+#              #
#    Updated: 2025/06/03 14:46:45 by ghenriqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name
NAME = fractol

# compiler and flags:
CC = cc
CFLAGS = -Wall -Wextra -Werror

# minilibx library:
MLX_DIR		= minilibx-linux
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -Lminilibx-linux -lmlx_Linux -lX11 -lXext

# basic and additional files:
SRC = 	0-main.c \
		1-init.c \
		2-render.c \
		hooks_events.c \
		math_utils.c

OBJ = $(SRC:.c=.o)

RM = rm -rf

# standard rule:
all: $(NAME)

# compile and create the lib:
$(NAME): $(MLX) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX) $(MLX_FLAGS) -o $(NAME)
	@echo "Let's gooo! Your $(NAME) is built, buddy!"

# compile .o:
%.o: %.c fractol.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiling $<..."

$(MLX):
	@echo "Making MiniLibX..."
	@make -C $(MLX_DIR)

# clean files:
clean:
	@$(RM) $(OBJ)
	@echo "Object files gone!"

# clean everything, .o and libft.a:
fclean: clean
	@$(RM) $(NAME)
	@echo "Binary gone!"

# recompile all:
re: fclean all

.PHONY: all re clean fclean
