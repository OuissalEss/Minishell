/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:55 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/29 07:24:44 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing/parsing.h"
#include "parsing/check_error/check_error.h"

int	exist(char **s)
{
	int		i;
	int		r;
	char	*str;

	i = 0;
	str = expand_dollar(*s);
	if (str == NULL)
	{
		g_data->exit_status = 0;
		exit (0);
	}
	while (str[i] && str[i] == ' ')
		i++;
	r = 1;
	if (str[i] == '\0')
		r = -1;
	free(str);
	str = NULL;
	return (r);
}

void	free_data(void)
{
	int			i;
	t_cmd		*cmd;

	cmd = g_data->commands;
	while (cmd)
	{
		g_data->commands = g_data->commands->next_cmd;
		if (cmd->infile != 0)
			close(cmd->infile);
		if (cmd->outfile != 1)
			close(cmd->outfile);
		free(cmd->cmd_name);
		cmd->cmd_name = NULL;
		i = 0;
		while (cmd->arguments && cmd->arguments[i])
		{
			free(cmd->arguments[i]);
			cmd->arguments[i] = NULL;
			i++;
		}
		free(cmd->arguments);
		cmd->arguments = NULL;
		free(cmd);
		cmd = NULL;
		cmd = g_data->commands;
	}
	g_data->commands = NULL;
}

void	print(void)
{
	int			i;
	t_cmd		*lst;
	t_red		*r;

	lst = g_data->commands;
	while (lst)
	{
		printf("cmd = %s\n", lst->cmd_name);
		i = 0;
		while (lst->arguments && lst->arguments[i])
		{
			printf("args[%d] = %s     ", i, lst->arguments[i]);
			i++;
		}
		printf("\ninfile = %d\n", lst->infile);
		printf("outfile = %d\n", lst->outfile);
		r = lst->red;
		while (r)
		{
			printf("r = %s   type = %d   fd[0] = %d   fd[1] = %d", r->file_name, r->type, r->fd[0], r->fd[1]);
			r = r->next;
		}
		printf("\n");
		lst = lst->next_cmd;
	}
}

void	env(void)
{
	t_env *tmp;

	tmp = g_data->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next_var;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void) argc;
	(void) argv;
	init_data(envp);
	while (1)
	{
		str = readline("my prompt > ");
		add_history(str);
		if (exist(&str) == 1 && check_error(str) == 1)
		{
			start_parsing(str);
			print();
			free_data();
		}
		if (str)
			free(str);
		str = NULL;
	}
	return (0);
}
