# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-ber <avan-ber@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/12 18:15:03 by avan-ber      #+#    #+#                  #
#    Updated: 2021/05/12 18:21:38 by avan-ber      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_one

CC = gcc
C++FLAGS = -Wall -Werror -Wextra -std=c++98 -pedantic

SRCS =	main.c \
		utils.c

all:$(NAME)

$(NAME):$(SRCS) philo_one.h
	$(CC) $(C++FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean alls

.PHONY: all clean fclean re
