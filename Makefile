# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slaajour <slaajour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/21 10:48:35 by oessamdi          #+#    #+#              #
#    Updated: 2022/12/10 23:20:17 by slaajour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = 	minishell.c \
		\
		parsing/handle_expansion.c parsing/expansion_array.c parsing/handle_quotes.c parsing/handle_redirections.c \
		parsing/lst_functions.c parsing/open_redirections.c parsing/split_cmd.c parsing/start_parsing.c \
		parsing/str_functions.c parsing/itoa.c parsing/init_data.c parsing/free_data.c parsing/open_heredoc.c \
		parsing/write_fd.c \
		\
		parsing/check_error/check_error.c parsing/check_error/error_flags.c parsing/check_error/expand.c \
		parsing/check_error/quotes_functions.c parsing/check_error/str_functions.c \
		\
		execution/start_executing.c execution/mini_utils.c execution/get_path.c \
		execution/path_utils.c execution/execution_utils.c execution/exit_status.c \
		\
		execution/builtins/do_cd.c execution/builtins/do_echo.c execution/builtins/do_env.c execution/builtins/do_exit.c \
		execution/builtins/do_export.c execution/builtins/export_utils.c execution/builtins/do_pwd.c execution/builtins/do_unset.c \

CC = @gcc 

CFLAGS = -Wall -Wextra -Werror

DEBUG = -fsanitize=address -g

REDFLAGS= -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include
OBJC = $(SRC:.c=.o)

RM = @rm -f

$(NAME) : $(OBJC)
			$(CC) $(CFLAGS)  $(OBJC) -o $(NAME) -lreadline
			@echo "MINISHELL CREATED!"

all : $(NAME)

debug :
	gcc  $(DEBUG) $(SRC) -lreadline -o $(NAME)

clean :
		$(RM) *.o parsing/*.o parsing/check_error/*.o execution/*.o execution/mini_utils/*.o execution/builtins/*.o
		@echo "All the .o files Removed"
fclean :
		$(RM) *.o parsing/*.o parsing/check_error/*.o execution/*.o execution/mini_utils/*.o execution/builtins/*.o
		$(RM) $(NAME)
		@echo "Executable removed"

re : fclean all

.PHONY:			all clean fclean re
