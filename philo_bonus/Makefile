# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: avan-ber <avan-ber@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2021/05/27 09:22:07 by avan-ber      #+#    #+#                  #
#    Updated: 2021/09/17 13:15:09 by avan-ber      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = gcc
CFLAGS = -Wall -Werror -Wextra

OBJ_DIR = objs
_OBJ_FILES =	main \
				error_messages_1 \
				error_messages_2 \
				parser \
				philo_init \
				philo_living \
				utils

OBJ_FILES = $(addsuffix .o, $(addprefix $(OBJ_DIR)/,$(_OBJ_FILES)))

all:$(NAME)

$(NAME):$(OBJ_FILES) philo_bonus.h
	$(CC) -o $(NAME) $(OBJ_FILES) $(LIB) $(CFLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $*)
	gcc -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean res
