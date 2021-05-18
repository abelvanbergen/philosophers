# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-ber <avan-ber@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/12 18:15:03 by avan-ber      #+#    #+#                  #
#    Updated: 2021/05/18 16:01:22 by avan-ber      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

CC = gcc
CLAGS = -Wall -Werror -Wextra

SRCS =	main.c \
		utils.c \
		error_messages.c \
		mutex.c \
		parser.c \
		philo_check.c \
		philo_init.c \
		philo_living.c

all:$(NAME)

$(NAME):$(SRCS) philo_one.h
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re
