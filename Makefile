# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 21:47:57 by ndo-vale          #+#    #+#              #
#    Updated: 2024/05/13 20:36:04 by ndo-vale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long
NAME_BONUS = so_long_bonus
CC	= cc
CFLAGS	= -Wall -Werror -Wextra -g
IFLAGS	= -I./ -I./include/ -lXext -lX11 -O3
LIBS	= mlx_linux/libmlx.a libft/libft.a
RM	= rm -rf

SRCS_DIR	= src
SRCS		= src/free_and_close.c src/is_map_valid.c src/main.c src/parse_map.c \
		  	src/pixel_helpers.c src/put_stuff.c src/sprite_helpers.c \
			src/update_frame.c
SRC_BONUS_DIR	= src_bonus
SRCS_BONUS	= src_bonus/free_and_close_bonus.c \
			src_bonus/get_frames_bonus.c \
			src_bonus/handle_player_mov_bonus.c \
			src_bonus/is_map_valid_bonus.c \
			src_bonus/main_bonus.c \
			src_bonus/parse_map_bonus.c \
		  	src_bonus/pixel_helpers_bonus.c \
		  	src_bonus/put_stuff_bonus.c \
		  	src_bonus/sprite_helpers_bonus.c \
			src_bonus/update_frame_bonus.c
OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

LIBFT = ./libft/libft.a
LIBFT_DIR = ./libft

MLX_DIR = ./mlx
MLX = ./mlx/libmlx.a

all: $(NAME)

bonus: $(NAME_BONUS)

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx_linux

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(IFLAGS) $(LIBS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(IFLAGS) $(LIBS)

.o:.c
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	make clean -C libft
	make clean -C mlx_linux
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

.PHONY: all clean fclean re
