# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mahmoud <mahmoud@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 15:45:59 by mahmoud           #+#    #+#              #
#    Updated: 2023/12/14 17:16:42 by mahmoud          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	./pipex.c ./utils.c \

SRC_B = ./pipex_bonus.c ./utils.c ./bonus_utils.c \
		
NAME = pipex
BONUS = pipex_bonus
AR = ar rs
RM = rm -f
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_P = ./libft/
LIBFT_AR = ./libft/libft.a

OBJS = $(SRC:.c=.o)
OBJS_B = $(SRC_B:.c=.o)

all: $(NAME)
bonus: $(BONUS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_B): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT_AR)
	$(CC) $(OBJS) $(LIBFT_AR) -o $(NAME)

$(BONUS): $(OBJS_B) $(LIBFT_AR)
	$(CC) $(OBJS_B) $(LIBFT_AR) -o $(BONUS)

$(LIBFT_AR):
	make -C $(LIBFT_P)

clean:
	make -C $(LIBFT_P) clean
	$(RM) $(OBJS)
	$(RM) $(OBJS_B)

fclean: clean
	make -C $(LIBFT_P) fclean
	$(RM) $(NAME)
	$(RM) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus

