# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/18 10:57:16 by samupedr          #+#    #+#              #
#    Updated: 2026/09/22 12:59:17 by samupedr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = push_swap
SRCS = push_swap.c push_swap_utils.c push_swap_utils_two.c push_swap_utils_three.c \
		ps_atoi.c ps_strcmp.c parse.c print_bench.c operations.c merge_sort.c \
		radix_sort.c selection_sort.c chunk_sort.c
OBJS = $(SRCS:.c=.o)
HEADERS = push_swap.h $(LIBFT_DIR)/libft.h

BONUS = checker
BONUS_SRCS = checker_bonus.c checker_parser_bonus.c vector_bonus.c \
		operations_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
BONUS_HEADERS = checker_bonus.h get_next_line_bonus.h $(LIBFT_DIR)/libft.h

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(LIBFT) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(BONUS)

$(LIBFT):
	make -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

$(OBJS): $(HEADERS)

$(BONUS_OBJS): $(BONUS_HEADERS)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
