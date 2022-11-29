# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 10:48:35 by oessamdi          #+#    #+#              #
#    Updated: 2022/11/29 07:21:58 by oessamdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = parsing/main.c parsing/init_data.c parsing/check_error.c parsing/parsing.c parsing/error_flags.c parsing/lst_functions.c \
	parsing/quotes_functions.c parsing/redirections.c parsing/str_functions.c parsing/expand.c parsing/str_utils.c

CC = @gcc 

CFLAGS = -Wall -Wextra -Werror 

DEBUG = -fsanitize=address -g

OBJC = $(SRC:.c=.o)

RM = @rm -f

$(NAME) : $(OBJC)
			$(CC) $(CFLAGS) $(DEBUG) -lreadline $(OBJC) -o $(NAME)
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
