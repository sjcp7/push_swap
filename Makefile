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
		insertion_sort.c radix_sort.c selection_sort.c chunk_sort.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) $^ $(LIBFT) -o $(NAME) 

%.o: %.c libft
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

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
