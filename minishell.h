/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:04 by oessamdi          #+#    #+#             */
/*   Updated: 2022/12/02 14:30:25 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define EOL '\0'

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <signal.h>

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next_var;
}				t_env;

typedef struct s_red
{
	char			*file_name;
	int				*arr;
	int				fd[2];
	int				type;
	int				expand;
	struct s_red	*next;
}				t_red;

typedef struct s_cmd
{
	char			*cmd_name;
	char			**arguments;
	int				infile;
	int				outfile;
	t_red			*red;
	struct s_cmd	*next_cmd;
}				t_cmd;

typedef struct s_data
{
	t_cmd	*commands;
	t_env	*env;
	int		exit_status;
	int		child_process;
	int		error;
}				t_data;

t_data	*g_data;

void	print(void);

#endif
