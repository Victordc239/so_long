# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vdiez-cu <vdiez-cu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/26 13:49:21 by vdiez-cu          #+#    #+#              #
#    Updated: 2025/06/05 14:15:10 by vdiez-cu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

SRCS		= get_next_line.c \
			main.c \
			get_next_line_utils.c \
			so_long_utils.c \
			comprobations.c \
			so_long.c \
			window_images.c \
			second_utils.c

OBJS		= $(SRCS:.c=.o)

MLX_DIR		= ./minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx.a

MLX_FLAGS	= -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR) all

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean

fclean:
	rm -f $(OBJS)
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re