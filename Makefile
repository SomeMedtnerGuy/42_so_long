# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ndo-vale <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/29 21:47:57 by ndo-vale          #+#    #+#              #
#    Updated: 2024/05/19 19:18:26 by ndo-vale         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long
NAME_BONUS = so_long_bonus
CC	= cc
CFLAGS	= -Wall -Werror -Wextra -g
IFLAGS	= -I./ -I./include/ -lXext -lX11 -O3
LIBS	= mlx_linux/libmlx.a libft/libft.a
RM	= rm -rf

SRC_DIR	= src
SRCS		= $(SRC_DIR)/check_map_validity.c \
			$(SRC_DIR)/free_and_close.c \
			$(SRC_DIR)/get_frames.c \
		  	$(SRC_DIR)/handle_player_mov.c \
		  	$(SRC_DIR)/main.c \
		  	$(SRC_DIR)/parse_map.c \
			$(SRC_DIR)/pixel_helpers.c \
			$(SRC_DIR)/put_stuff.c \
			$(SRC_DIR)/render_next_frame.c \
			$(SRC_DIR)/sprite_helpers.c
SRC_BONUS_DIR	= src_bonus
SRCS_BONUS	= $(SRC_BONUS_DIR)/check_map_validity_bonus.c \
			$(SRC_BONUS_DIR)/free_and_close_bonus.c \
			$(SRC_BONUS_DIR)/get_frames_bonus.c \
			$(SRC_BONUS_DIR)/handle_player_mov_bonus.c \
			$(SRC_BONUS_DIR)/main_bonus.c \
			$(SRC_BONUS_DIR)/parse_map_bonus.c \
		  	$(SRC_BONUS_DIR)/pixel_helpers_bonus.c \
			$(SRC_BONUS_DIR)/put_effects_bonus.c \
		  	$(SRC_BONUS_DIR)/put_stuff_bonus.c \
		  	$(SRC_BONUS_DIR)/sprite_helpers_bonus.c \
			$(SRC_BONUS_DIR)/render_next_frame_bonus.c
OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./mlx_linux
MLX = $(MLX_DIR)/libmlx.a

all: $(NAME)

bonus: $(NAME_BONUS)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(IFLAGS) $(LIBS)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(IFLAGS) $(LIBS)

.o:.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS) $(OBJS_BONUS)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

.PHONY: all clean fclean re
