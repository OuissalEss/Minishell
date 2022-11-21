# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 10:48:35 by oessamdi          #+#    #+#              #
#    Updated: 2022/11/21 10:48:36 by oessamdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c init_data.c check_error.c parsing.c error_flags.c lst_functions.c \
	quotes_functions.c redirections.c str_functions.c

CC = @gcc 

CFLAGS = -Wall -Wextra -Werror 

DEBUG = -fsanitize=address -g

OBJC = $(SRC:.c=.o)

RM = @rm -f

$(NAME) : $(OBJC)
			$(CC) $(CFLAGS)  -lreadline $(OBJC) -o $(NAME)
			@echo "MINISHELL CREATED!"

all : $(NAME)

debug :
	gcc  $(DEBUG) $(SRC) -lreadline -o $(NAME)

clean :
		$(RM) *.o
		@echo "Removed all the .o files"
fclean :
		$(RM) *.o
		$(RM) $(NAME)
		@echo "Removed executble"

re : fclean all

.PHONY:			all clean fclean re
