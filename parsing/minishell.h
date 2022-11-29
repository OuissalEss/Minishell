/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:04 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 05:04:07 by oessamdi         ###   ########.fr       */
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

typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next_var;
}				t_env;

typedef struct s_heredoc
{
	char				*dlmt;
	int					fd[2];
	struct s_heredoc	*next;
}			t_heredoc;

typedef struct s_red
{
	char			*file_name;
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
	t_heredoc		*hdoc;
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

#endif
