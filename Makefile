# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 19:27:43 by crigonza          #+#    #+#              #
#    Updated: 2023/11/14 10:19:36 by crigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= cub3d
BONUS	= cub3d_bonus
CFLAGS	= -Werror -Wextra -Wall -w -Wunreachable-code -Ofast

LIBMLX	= ./MLX42
LIBFT	= ./Libft

HEADERS	= -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
# LIBS	= -lglfw -L /opt/homebrew/cellar/glfw/3.3.8/lib $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
SRCS	= src/check_map.c src/checker.c src/controls.c src/draw.c \
			src/free_utils.c src/hooks.c src/initialize.c src/main.c \
			src/minimap.c src/parse_utils.c src/parser.c src/raycast.c \
			src/texture.c src/utils.c
BONUS_SRCS	= $(shell find ./bonus -iname "*.c")
OBJS	= ${SRCS:.c=.o}
BONUS_OBJS	= ${BONUS_SRCS:.c=.o}


all: libft libmlx $(NAME)

bonus: libft libmlx $(BONUS)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@$(MAKE) -C $(LIBMLX)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	
$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(BONUS): $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(BONUS)

clean:
	@rm -f $(OBJS)
	@rm -f $(BONUS_OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft