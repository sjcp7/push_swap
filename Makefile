# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/09/18 10:57:16 by samupedr          #+#    #+#              #
#    Updated: 2026/09/18 13:20:57 by ljanuari         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE_DIR = includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

NAME = push_swap
SRCS = src/push_swap.c src/push_swap_utils.c src/push_swap_utils_two.c src/push_swap_utils_three.c \
		src/ps_atoi.c src/ps_strcmp.c src/parse.c src/print_bench.c src/operations.c src/merge_sort.c algorithms/bubble_sort.c  \
		algorithms/insertion_sort.c algorithms/radix_sort.c algorithms/selection_sort.c algorithms/chunk_sort.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) $^ $(LIBFT) -o $(NAME) 

%.o: %.c libft
	$(CC) $(CFLAGS) -I $(INCLUDE_DIR) -c $< -o $@

libft:
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re libft
