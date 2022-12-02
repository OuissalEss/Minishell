# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 10:48:35 by oessamdi          #+#    #+#              #
#    Updated: 2022/12/02 15:21:33 by oessamdi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	minishell.c print.c \
		parsing/handle_expansion.c parsing/handle_quotes.c parsing/handle_redirections.c \
		parsing/lst_functions.c parsing/open_redirections.c parsing/split_cmd.c parsing/start_parsing.c \
		parsing/str_functions.c parsing/itoa.c parsing/init_data.c parsing/free_data.c parsing/open_heredoc.c \
		parsing/write_fd.c \
		parsing/check_error/check_error.c parsing/check_error/error_flags.c parsing/check_error/expand.c \
		parsing/check_error/quotes_functions.c parsing/check_error/str_functions.c

CC = @gcc 

CFLAGS = -Wall -Wextra -Werror 

DEBUG = -fsanitize=address -g

OBJC = $(SRC:.c=.o)

RM = @rm -f

$(NAME) : $(OBJC)
			$(CC) $(CFLAGS) -lreadline $(OBJC) -o $(NAME)
			@echo "MINISHELL CREATED!"

all : $(NAME)

debug :
	gcc  $(DEBUG) $(SRC) -lreadline -o $(NAME)

clean :
		$(RM) *.o parsing/*.o parsing/check_error/*.o
		@echo "Removed all the .o files"
fclean :
		$(RM) *.o parsing/*.o parsing/check_error/*.o
		$(RM) $(NAME)
		@echo "Removed executable"

re : fclean all

.PHONY:			all clean fclean re
