# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: crigonza <crigonza@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/18 19:27:43 by crigonza          #+#    #+#              #
#    Updated: 2023/10/18 19:10:51 by crigonza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# //= Variables =//

NAME	= cub3d
CFLAGS	= -Werror -Wextra -Wall -w -Wunreachable-code -Ofast
LIBMLX	= ./MLX42
LIBFT	= ./Libft
/* GNL		= ./GNL */

HEADERS	= -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS	= -lglfw -L /opt/homebrew/cellar/glfw/3.3.8/lib $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a
SRCS	= $(shell find ./src -iname "*.c")
OBJS	= ${SRCS:.c=.o}

BOLD	= \033[1m
BLUE	= \033[34;1m
RESET	= \033[0m

# //= Recipes =//

all: libft libmlx $(NAME)

bonus: libft libmlx $(BONUS)

libft:
	@$(MAKE) -C $(LIBFT)

libmlx:
	@$(MAKE) -C $(LIBMLX)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "$(BLUE)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(BONUS): $(BONUS_OBJS)
	@$(CC) $(BONUS_OBJS) $(LIBS) $(HEADERS) -o $(NAME)

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