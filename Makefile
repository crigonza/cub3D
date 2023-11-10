# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 19:27:43 by crigonza          #+#    #+#              #
#    Updated: 2023/11/08 08:12:43 by crigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	= cub3d
CFLAGS	= -Werror -Wextra -Wall -w -Wunreachable-code -Ofast

LIBMLX	= ./MLX42
LIBFT	= ./Libft

HEADERS	= -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/include
/*LIBS	= -lglfw -L /Users/$(USER)/.brew/opt/glfw/lib/ $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a*/
LIBS	= -lglfw -L /opt/homebrew/cellar/glfw/3.3.8/lib $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
SRCS	= $(shell find ./src -iname "*.c")
OBJS	= ${SRCS:.c=.o}


all: libft libmlx $(NAME)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@$(MAKE) -C $(LIBMLX)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft