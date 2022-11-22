/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:48:55 by oessamdi          #+#    #+#             */
/*   Updated: 2022/11/22 18:10:25 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

int	exist(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		g_data->exit_status = 0;
		exit (0);
	}
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (-1);
	return (1);
}

void	free_data(void)
{
	int			i;
	t_cmd		*cmd;
	t_heredoc	*hd;

	cmd = g_data->commands;
	while (cmd)
	{
		g_data->commands = g_data->commands->next_cmd;
		// close infile and outfile
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
		hd = cmd->hdoc;
		while (hd)
		{
			cmd->hdoc = cmd->hdoc->next;
			free(hd->dlmt);
			hd->dlmt = NULL;
			free(hd);
			hd = NULL;
			hd = cmd->hdoc;
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
	t_heredoc	*hlst;

	printf("HELLOLLLL\n");
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
		hlst = lst->hdoc;
		while (hlst)
		{
			printf("hdoc = %s      ", hlst->dlmt);
			hlst = hlst->next;
		}
		printf("\n");
		lst = lst->next_cmd;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;

	(void) argc;
	(void) argv;
	init_data(envp);
	// t_env *tmp = g_data->env;
	// while (tmp)
	// {
	// 	printf("%s=%s.\n", tmp->var, tmp->value);
	// 	tmp = tmp->next_var;
	// }
	while (1)
	{
		str = readline("my prompt : ");
		add_history(str);
		if (exist(str) == 1 && check_error(str) == 1)
		{
			if (start_parsing(str) == 1)
			{
				printf("Rah ma segfaultach\n");
				str = expand_dollar(str);
				printf("str = %s.\n", str);
				print();
				free_data();
			}
		}
		if (str)
			free(str);
		str = NULL;
	}
	return (0);
}
